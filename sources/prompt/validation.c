/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:36:25 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 12:57:50 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
