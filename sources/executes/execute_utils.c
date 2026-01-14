/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:49 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 14:17:42 by hho-jia-         ###   ########.fr       */
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
