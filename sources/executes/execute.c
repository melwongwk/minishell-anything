/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:44 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/16 18:20:24 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		last_status;
	pid_t	last_pid;

	close_fds(data->cmd, false);
	last_status = 0;
	last_pid = data->pid;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid <= 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = status;
		}
	}
	return (last_status);
}

static	void	create_children_helper(t_data *data, t_command *cmd, int in)
{
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
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
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

static int	is_builtin(char *cmd)
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

int	execute(t_data *data)
{
	int		ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
	{
		set_exit_status(data, ret);
		return (ret);
	}
	if (!data->cmd->pipe_output && !data->cmd->prev)
	{
		if (!check_infile_outfile(data->cmd->io_fds))
		{
			set_exit_status(data, EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		if (is_builtin(data->cmd->command))
		{
			redirect_io(data->cmd->io_fds);
			ret = execute_builtin(data, data->cmd);
			if (restore_io(data->cmd->io_fds) == false)
				return (EXIT_FAILURE);
			set_exit_status(data, ret);
			return (ret);
		}
	}
	ret = create_children(data);
	set_exit_status(data, ret);
	return (ret);
}
