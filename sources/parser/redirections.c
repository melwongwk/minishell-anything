/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:55:33 by melwong           #+#    #+#             */
/*   Updated: 2026/01/17 13:45:16 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_input(t_io_fds *io, char *filename)
{
	if (!open_infile(io, filename))
	{
		io->redir_error = true;
		return (0);
	}
	free_ptr(io->infile);
	io->infile = filename;
	return (1);
}

static int	handle_output(t_io_fds *io, char *filename, bool append)
{
	if (!open_outfile(io, filename, append))
	{
		io->redir_error = true;
		return (0);
	}
	free_ptr(io->outfile);
	io->outfile = filename;
	return (1);
}

static void	handle_heredoc(t_io_fds *io, char *delimiter, int status)
{
	free_ptr(io->heredoc_delimiter);
	io->heredoc_delimiter = delimiter;
	io->heredoc_quotes = (status != DEFAULT);
}

static int	process_redir(t_command *cmd,
	t_token *tok, char *filename, int status)
{
	if (tok->type == INPUT)
		return (handle_input(cmd->io_fds, filename));
	else if (tok->type == TRUNC)
		return (handle_output(cmd->io_fds, filename, false));
	else if (tok->type == APPEND)
		return (handle_output(cmd->io_fds, filename, true));
	else if (tok->type == HEREDOC)
		return (handle_heredoc(cmd->io_fds, filename, status), 1);
	return (0);
}

void	handle_redir_token(t_command *cmd, t_token **tok)
{
	t_token	*delim;
	t_token	*orig_tok;
	char	*joined;
	int		delim_status;

	orig_tok = *tok;
	delim = find_and_advance_tokens(tok, cmd, &delim_status);
	if (!delim)
		return ;
	joined = build_filename(delim);
	if (!process_redir(cmd, orig_tok, joined, delim_status))
		free(joined);
}
