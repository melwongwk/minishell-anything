/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:03:34 by melwong           #+#    #+#             */
/*   Updated: 2026/01/18 08:03:34 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_token_strings(t_token *t, const char *s)
{
	if (s)
	{
		t->str = ft_strdup(s);
		t->str_backup = ft_strdup(s);
	}
	else
	{
		t->str = NULL;
		t->str_backup = NULL;
	}
}

static void	init_token_fields(t_token *t, int type, int status)
{
	t->type = type;
	t->status = status;
	t->join = false;
	t->prev = NULL;
	t->next = NULL;
}

t_token	*token_new(const char *s, int type, int status)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	set_token_strings(t, s);
	init_token_fields(t, type, status);
	return (t);
}

static void	join_token_pair(t_token *cur, t_token *next)
{
	char	*joined;
	char	*left;
	char	*right;

	if (cur->str)
		left = cur->str;
	else
		left = "";
	if (next->str)
		right = next->str;
	else
		right = "";
	joined = ft_strjoin(left, right);
	free(cur->str);
	cur->str = joined;
	cur->next = next->next;
	if (next->next)
		next->next->prev = cur;
	free(next->str);
	free(next->str_backup);
	free(next);
}

void	join_tokens(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	while (cur && cur->next)
	{
		if (cur->next->join)
		{
			join_token_pair(cur, cur->next);
			continue ;
		}
		cur = cur->next;
	}
}
