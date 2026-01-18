/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:20:59 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 18:00:18 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_interrupt(t_data *data)
{
	if (!data->heredoc_interrupted)
		return (0);
	set_exit_status(data, 130);
	free_data(data, false);
	data->heredoc_interrupted = false;
	return (1);
}

static void	fork_heredoc_process(t_command *cmd, char **envp,
				int last_status, t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(cmd, envp, last_status, fd[1]);
		close(fd[1]);
		exit(0);
	}
	heredoc_parent(pid, cmd, data, fd);
}

void	prepare_heredoc(t_command *cmd, char **envp, int last_status,
			t_data *data)
{
	if (!cmd->io_fds->heredoc_delimiter)
		return ;
	fork_heredoc_process(cmd, envp, last_status, data);
}

void	handle_heredocs(t_command *cmds, char **envp, int last_status,
			t_data *data)
{
	while (cmds)
	{
		prepare_heredoc(cmds, envp, last_status, data);
		if (data->heredoc_interrupted)
			return ;
		cmds = cmds->next;
	}
}
