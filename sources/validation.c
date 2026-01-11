/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:36:25 by melwong           #+#    #+#             */
/*   Updated: 2026/01/11 13:36:27 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
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
