/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:11:58 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/17 13:47:30 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_io_fds *io, char *filename)
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

int	open_outfile(t_io_fds *io, char *filename, bool append)
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

char	*build_filename(t_token *delim)
{
	char	*joined;
	char	*tmp;

	joined = ft_strdup(delim->str);
	delim = delim->next;
	while (delim && delim->join)
	{
		tmp = joined;
		joined = ft_strjoin(tmp, delim->str);
		free(tmp);
		delim = delim->next;
	}
	return (joined);
}

t_token	*find_and_advance_tokens(t_token **tok,
	t_command *cmd, int *delim_status)
{
	t_token	*cur;
	t_token	*delim;

	cur = (*tok)->next;
	while (cur && cur->type != WORD && cur->type != VAR)
		cur = cur->next;
	if (!cur)
	{
		*tok = (*tok)->next;
		return (NULL);
	}
	delim = cur;
	*delim_status = delim->status;
	cur = cur->next;
	while (cur && cur->join)
		cur = cur->next;
	if (cmd->io_fds->redir_error)
	{
		*tok = cur;
		return (NULL);
	}
	*tok = cur;
	return (delim);
}
