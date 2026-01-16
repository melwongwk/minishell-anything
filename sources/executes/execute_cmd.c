/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:52 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/16 16:42:12 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(data);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(data, cmd->args);
	return (ret);
}

static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		return (errcmd_msg("execve", NULL, strerror(errno), errno));
	return (CMD_NOT_FOUND);
}

static	int	execute_local_bin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = check_command_found(cmd);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errcmd_msg("execve",
				NULL, strerror(errno), errno));
	return (CMD_NOT_FOUND);
}

void	execute_command(t_data *data, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_shell(data, errcmd_msg("execute_command",
				NULL, "parsing error: no command to execute!", EXIT_FAILURE));
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
		exit_shell(data, errcmd_msg(cmd->command, NULL,
				"command not found", CMD_NOT_FOUND));
	}
	ret = execute_local_bin(data, cmd);
	exit_shell(data, ret);
}
