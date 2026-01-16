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

void	prepare_heredoc(t_command *cmd, char **envp, int last_status, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*line;
	char	*expanded;

	if (!cmd->io_fds->heredoc_delimiter)
		return ;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				write(STDOUT_FILENO, "\n", 1);
				break ;
			}
			if (ft_strcmp(line, cmd->io_fds->heredoc_delimiter) == 0)
			{
				free(line);
				break ;
			}
			if (!cmd->io_fds->heredoc_quotes)
			{
				expanded = expand_string(line, envp, last_status);
				if (expanded)
				{
					free(line);
					line = expanded;
				}
			}
			if (line)
			{
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
			}
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(fd[0]);
			cmd->io_fds->fd_in = -1;
			data->heredoc_interrupted = true;
			set_exit_status(data, 130);
			signal(SIGINT, SIG_DFL);
			return ;
		}
		cmd->io_fds->fd_in = fd[0];
		signal(SIGINT, SIG_DFL);
	}
}

void	handle_heredocs(t_command *cmds, char **envp, int last_status, t_data *data)
{
	while (cmds)
	{
		prepare_heredoc(cmds, envp, last_status, data);
		if (data->heredoc_interrupted)
			return ;
		cmds = cmds->next;
	}
}
