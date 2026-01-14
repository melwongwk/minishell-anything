/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 16:05:30 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", "restore stdin", strerror(errno), false);
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", "restore stdout", strerror(errno), false);
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

static int	redirect_helper(int backup_fd, int fd_new, char *infile)
{
	backup_fd = dup(STDIN_FILENO);
	if (backup_fd == -1)
		return (errmsg_cmd("dup", "std backup", strerror(errno), false));
	if (dup2(fd_new, STDIN_FILENO) == -1)
		return (errmsg_cmd("dup2", infile, strerror(errno), false));
	close (fd_new);
	fd_new = -1;
	return (true);
}

int	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->fd_in != -1)
		ret = redirect_helper(io->stdin_backup, io->fd_in, io->infile);
	if (io->fd_out != -1)
		ret = redirect_helper(io->stdin_backup, io->fd_in, io->infile);
	return (ret);
}

int	redirect_each_cmd_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->fd_in != -1)
	{
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
		close(io->fd_out);
		io->fd_out = -1;
	}
	return (ret);
}

int	check_infile_outfile(t_io_fds *io_fds)
{
	if (!io_fds || (!io_fds->infile && !io_fds->outfile))
		return (1);
	if ((io_fds->infile && io_fds->fd_in == -1)
		|| (io_fds->outfile && io_fds->fd_out == -1))
		return (0);
	return (1);
}
