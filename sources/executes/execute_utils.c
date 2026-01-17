/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:49 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/17 13:49:48 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_is_dir(char *cmd)
{
	struct stat	path_stat;

	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	check_command_found(t_command *cmd)
{
	if (access(cmd->command, F_OK) != 0)
		return (errcmd_msg(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (errcmd_msg(cmd->command,
				NULL, "is a directory", CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, X_OK) != 0)
		return (errcmd_msg(cmd->command,
				NULL, strerror(errno), CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
