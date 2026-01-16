/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/16 17:38:19 by hho-jia-         ###   ########.fr       */
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
			ret = errcmd_msg("dup2", "restore stdin", strerror(errno), false);
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = errcmd_msg("dup2", "restore stdout", strerror(errno), false);
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

static int	redirect_helper(int *backup_fd, int fd_new, int std_fd, char *file)
{
	int	dup_fd;

	dup_fd = dup(std_fd);
	if (dup_fd == -1)
		return (errcmd_msg("dup", "std backup", strerror(errno), false));
	*backup_fd = dup_fd;
	if (dup2(fd_new, std_fd) == -1)
		return (errcmd_msg("dup2", file, strerror(errno), false));
	close(fd_new);
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
	{
		if (!redirect_helper(&io->stdin_backup, io->fd_in, STDIN_FILENO, io->infile))
			return (false);
	}
	if (io->fd_out != -1)
	{
		if (!redirect_helper(&io->stdout_backup, io->fd_out, STDOUT_FILENO, io->outfile))
			return (false);
	}
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
			ret = errcmd_msg("dup2", io->infile, strerror(errno), false);
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errcmd_msg("dup2", io->outfile, strerror(errno), false);
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
