/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:55:33 by melwong           #+#    #+#             */
/*   Updated: 2026/01/09 06:55:33 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static t_token	*next_word(t_token *tok)
{
	while (tok && tok->type != WORD)
		tok = tok->next;
	return (tok);
}

void	handle_redir_token(t_command *cmd, t_token **tok)
{
	t_token	*next;

	next = (*tok)->next;
	next = next_word(next);
	if (!next)
		return ;

	if ((*tok)->type == INPUT)
		cmd->io_fds->infile = ft_strdup(next->str);
	else if ((*tok)->type == TRUNC || (*tok)->type == APPEND)
		cmd->io_fds->outfile = ft_strdup(next->str);
	else if ((*tok)->type == HEREDOC)
	{
		cmd->io_fds->heredoc_delimiter = ft_strdup(next->str);
		cmd->io_fds->heredoc_quotes = (next->status != DEFAULT);
	}
	*tok = next->next;
}

