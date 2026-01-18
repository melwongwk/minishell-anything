/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:42:09 by melwong           #+#    #+#             */
/*   Updated: 2026/01/17 23:42:09 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_expand_line(char *line, t_command *cmd, char **envp,
				int last_status)
{
	char	*expanded;

	if (cmd->io_fds->heredoc_quotes)
		return (line);
	expanded = expand_string(line, envp, last_status);
	if (!expanded)
		return (line);
	free(line);
	return (expanded);
}

void	heredoc_child(t_command *cmd, char **envp, int last_status,
			int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, cmd->io_fds->heredoc_delimiter))
		{
			free(line);
			break ;
		}
		line = heredoc_expand_line(line, cmd, envp, last_status);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static void	heredoc_parent_sigint(t_command *cmd, t_data *data, int read_fd)
{
	close(read_fd);
	cmd->io_fds->fd_in = -1;
	data->heredoc_interrupted = true;
	set_exit_status(data, 130);
	init_signals();
}

static void	heredoc_parent_success(t_command *cmd, int read_fd)
{
	cmd->io_fds->fd_in = read_fd;
	init_signals();
}

void	heredoc_parent(pid_t pid, t_command *cmd, t_data *data, int fd[2])
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		heredoc_parent_sigint(cmd, data, fd[0]);
		return ;
	}
	heredoc_parent_success(cmd, fd[0]);
}
