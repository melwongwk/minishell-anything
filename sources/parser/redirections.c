/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:55:33 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 19:50:27 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(t_io_fds *io, char *filename)
{
	if (io->fd_in != -1)
		close(io->fd_in);
	io->fd_in = open(filename, O_RDONLY);
	if (io->fd_in == -1)
	{
		errcmd_msg(filename, NULL, strerror(errno), 0);
		return (0);
	}
	return (1);
}

static int	open_outfile(t_io_fds *io, char *filename, bool append)
{
	if (io->fd_out != -1)
		close(io->fd_out);
	if (append)
		io->fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		io->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		errcmd_msg(filename, NULL, strerror(errno), 0);
		return (0);
	}
	return (1);
}

void	handle_redir_token(t_command *cmd, t_token **tok)
{
	t_token	*cur;
	t_token	*delim;
	char	*joined;
	char	*tmp;

	cur = (*tok)->next;
	while (cur && cur->type != WORD && cur->type != VAR)
		cur = cur->next;
	if (!cur)
	{
		*tok = (*tok)->next;
		return ;
	}
	delim = cur;
	joined = ft_strdup(cur->str);
	cur = cur->next;
	while (cur && cur->join)
	{
		tmp = joined;
		joined = ft_strjoin(tmp, cur->str);
		free(tmp);
		cur = cur->next;
	}
	if ((*tok)->type == INPUT)
	{
		if (!open_infile(cmd->io_fds, joined))
		{
			free(joined);
			*tok = cur;
			return ;
		}
		free_ptr(cmd->io_fds->infile);
		cmd->io_fds->infile = joined;
	}
	else if ((*tok)->type == TRUNC)
	{
		if (!open_outfile(cmd->io_fds, joined, false))
		{
			free(joined);
			*tok = cur;
			return ;
		}
		free_ptr(cmd->io_fds->outfile);
		cmd->io_fds->outfile = joined;
		cmd->io_fds->append = false;
	}
	else if ((*tok)->type == APPEND)
	{
		if (!open_outfile(cmd->io_fds, joined, true))
		{
			free(joined);
			*tok = cur;
			return ;
		}
		free_ptr(cmd->io_fds->outfile);
		cmd->io_fds->outfile = joined;
		cmd->io_fds->append = true;
	}
	else if ((*tok)->type == HEREDOC)
	{
		free_ptr(cmd->io_fds->heredoc_delimiter);
		cmd->io_fds->heredoc_delimiter = joined;
		cmd->io_fds->heredoc_quotes = (delim->status != DEFAULT);
	}
	*tok = cur;
}
