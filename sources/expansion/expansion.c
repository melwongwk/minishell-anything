/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 07:13:45 by melwong           #+#    #+#             */
/*   Updated: 2026/01/20 15:40:14 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_heredoc_delim(t_token *token)
{
	return (token->prev && token->prev->type == HEREDOC);
}

static int	should_expand_token(t_token *t)
{
	if (!t->str)
		return (0);
	if (is_heredoc_delim(t))
		return (0);
	if (t->status == SQUOTE)
		return (0);
	return (1);
}

static void	expand_token_str(t_token *t, char **envp, int last_status)
{
	char	*expanded;

	expanded = expand_string(t->str, envp, last_status);
	free(t->str);
	t->str = expanded;
	t->type = WORD;
}

static int	post_expand_cleanup(t_token **tokens, t_token *t, int orig_status)
{
	if (!t->str || !*t->str)
	{
		remove_token(tokens, t);
		return (1);
	}
	if (orig_status == DEFAULT && t->type == WORD
		&& has_whitespace(t->str) && !t->is_assign)
		split_token_on_whitespace(t);
	return (0);
}

void	expand_tokens(t_token **tokens, char **envp, int last_status)
{
	t_token	*t;
	t_token	*next;
	int		orig_status;

	if (!tokens || !*tokens)
		return ;
	t = *tokens;
	while (t)
	{
		next = t->next;
		orig_status = t->status;
		if ((t->type == WORD || t->type == VAR) && should_expand_token(t))
			expand_token_str(t, envp, last_status);
		if (post_expand_cleanup(tokens, t, orig_status))
		{
			t = next;
			continue ;
		}
		t = t->next;
	}
}
