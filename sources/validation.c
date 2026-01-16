/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:36:25 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 16:39:30 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_unclosed_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_syntax(t_token *token)
{
	if (!token)
		return (true);
	if (token->type == PIPE)
		return (false);
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
				return (false);
		}
		if (token->type == INPUT || token->type == HEREDOC
			|| token->type == TRUNC || token->type == APPEND)
		{
			if (!token->next || (token->next->type != WORD
					&& token->next->type != VAR))
				return (false);
		}
		token = token->next;
	}
	return (true);
}
