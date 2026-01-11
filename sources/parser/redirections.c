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
		cmd->io_fds->infile = joined;
	else if ((*tok)->type == TRUNC || (*tok)->type == APPEND)
		cmd->io_fds->outfile = joined;
	else if ((*tok)->type == HEREDOC)
	{
		cmd->io_fds->heredoc_delimiter = joined;
		cmd->io_fds->heredoc_quotes = (delim->status != DEFAULT);
	}
	*tok = cur;
}

