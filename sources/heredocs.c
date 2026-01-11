/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:20:59 by melwong           #+#    #+#             */
/*   Updated: 2026/01/11 22:20:59 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libft.h"

void prepare_heredoc(t_command *cmd, t_env *env, int last_status)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*line;

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
			if (!line || !ft_strcmp(line, cmd->io_fds->heredoc_delimiter))
				break ;
			if (!cmd->io_fds->heredoc_quotes)
				line = expand_string(line, env, last_status);

			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
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
		cmd->io_fds->fd_in = fd[0];
		signal(SIGINT, SIG_DFL);
	}
}

void	handle_heredocs(t_command *cmds, t_env *env, int last_status)
{
	while (cmds)
	{
		if (cmds->io_fds->heredoc_delimiter)
			prepare_heredoc(cmds, env, last_status);
		cmds = cmds->next;
	}
}
