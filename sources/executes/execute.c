/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:44 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/16 16:45:52 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_children(t_data *data, pid_t last_pid)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == last_pid)
			save_status = status;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static	void	create_children_helper(t_data *data, t_command *cmd, int in)
{
	close_unused_pipe_fds(data, cmd);
	if (cmd != data->cmd && in >= 0)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->next)
	{
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
	}
	if (!open_io_files(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	if (redirect_each_cmd_io(cmd->io_fds) == false)
		exit_shell(data, EXIT_FAILURE);
	execute_command(data, cmd);
}

static	int	create_children(t_data *data)
{
	t_command	*cmd;
	int			in;
	pid_t		last_pid;

	in = -1;
	last_pid = 0;
	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe_fd) == -1)
			return (errcmd_msg("pipe", NULL, strerror(errno), EXIT_FAILURE));
		data->pid = fork();
		if (data->pid == -1)
			return (errcmd_msg("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			create_children_helper(data, cmd, in);
		}
		last_pid = data->pid;
		if (cmd != data->cmd && in >= 0)
			close(in);
		if (cmd->next)
		{
			close(cmd->pipe_fd[1]);
			in = cmd->pipe_fd[0];
		}
		cmd = cmd->next;
	}
	return (get_children(data, last_pid));
}

static	int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (CMD_NOT_FOUND);
}

int	execute(t_data *data)
{
	int		ret;

	if (!data)
		return (EXIT_FAILURE);
	ret = CMD_NOT_FOUND;
	if (data->cmd && data->cmd->io_fds
		&& data->cmd->io_fds->heredoc_delimiter
		&& data->cmd->io_fds->fd_in == -1)
	{
		set_exit_status(data, 130);
		return (130);
	}
	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
	{
		set_exit_status(data, ret);
		return (ret);
	}
	if (!data->cmd->pipe_output && !data->cmd->prev)
	{
		if (!open_io_files(data->cmd->io_fds))
		{
			set_exit_status(data, EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		redirect_io(data->cmd->io_fds);
		ret = execute_builtin(data, data->cmd);
		if (restore_io(data->cmd->io_fds) == false)
			return (EXIT_FAILURE);
	}
	if (ret != CMD_NOT_FOUND)
	{
		set_exit_status(data, ret);
		return (ret);
	}
	ret = create_children(data);
	set_exit_status(data, ret);
	return (ret);
}
