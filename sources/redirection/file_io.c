/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/16 16:47:44 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

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

static int	open_intermediate_outputs(t_io_fds *io)
{
	int	i;
	int	fd;
	int	count;

	if (!io->outfiles)
		return (true);
	count = 0;
	while (io->outfiles[count])
		count++;
	i = 0;
	while (i < count - 1)
	{
		if (io->out_append && io->out_append[i])
			fd = open(io->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(io->outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			errcmd_msg(io->outfiles[i], NULL, strerror(errno), 0);
			return (false);
		}
		close(fd);
		i++;
	}
	return (true);
}

static int	open_intermediate_inputs(t_io_fds *io)
{
	int	i;
	int	fd;
	int	count;

	if (!io->infiles)
		return (true);
	count = 0;
	while (io->infiles[count])
		count++;
	i = 0;
	while (i < count - 1)
	{
		fd = open(io->infiles[i], O_RDONLY);
		if (fd == -1)
		{
			errcmd_msg(io->infiles[i], NULL, strerror(errno), 0);
			return (false);
		}
		close(fd);
		i++;
	}
	return (true);
}

static int	open_outputs(t_io_fds *io)
{
	if (!open_intermediate_outputs(io))
		return (false);
	if (io->outfile)
	{
		if (io->append)
			io->fd_out = open(io->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			io->fd_out = open(io->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (io->fd_out == -1)
		{
			errcmd_msg(io->outfile, NULL, strerror(errno), 0);
			return (false);
		}
	}
	return (true);
}

static int	open_inputs(t_io_fds *io)
{
	if (!open_intermediate_inputs(io))
		return (false);
	if (io->infile)
	{
		io->fd_in = open(io->infile, O_RDONLY);
		if (io->fd_in == -1)
		{
			errcmd_msg(io->infile, NULL, strerror(errno), 0);
			return (false);
		}
	}
	return (true);
}

int	open_io_files(t_io_fds *io)
{
	if (!io)
		return (true);
	if (io->input_first)
	{
		if (!open_inputs(io))
			return (false);
		if (!open_outputs(io))
		{
			if (io->fd_in != -1)
			{
				close(io->fd_in);
				io->fd_in = -1;
			}
			return (false);
		}
	}
	else
	{
		if (!open_outputs(io))
			return (false);
		if (!open_inputs(io))
		{
			if (io->fd_out != -1)
			{
				close(io->fd_out);
				io->fd_out = -1;
			}
			return (false);
		}
	}
	return (true);
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
