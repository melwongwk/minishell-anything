/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:44 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 16:31:19 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_children(t_data *data)
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
		if (wpid == data->pid)
			save_status = status;
		continue ;
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
	if (cmd != data->cmd)
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
	if (redirect_each_cmd_io(cmd->io_fds) == false)
		exit_shell(data, EXIT_FAILURE);
	execute_command(data, cmd);
}

static	int	create_children(t_data *data)
{
	t_command	*cmd;
	int			in;
	
	in = -1;
	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		if (cmd->next && pipe(cmd->pipe_fd) == -1)
			return (errcmd_msg("pipe", NULL, strerror(errno), EXIT_FAILURE));
		data->pid = fork();
		if (data->pid == -1)
			return (errcmd_msg("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			create_children_helper(data, cmd, in);
		if (cmd != data->cmd && in >= 0)
			close(in);
		if (cmd->next)
		{
			close(cmd->pipe_fd[1]);
			in = cmd->pipe_fd[0];
		}
		cmd = cmd->next;
	}
	return (get_children(data));
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
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd->io_fds))
	{
		if (redirect_io(data->cmd->io_fds) == false)
			return (EXIT_FAILURE);
		ret = execute_builtin(data, data->cmd);
		if (restore_io(data->cmd->io_fds) == false)
			return (EXIT_FAILURE);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}
