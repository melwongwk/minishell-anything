/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:14:32 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 12:58:18 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(const char *s, int type, int status)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
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
	t->var_exists = false;
	t->type = type;
	t->status = status;
	t->join = false;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}

void	token_append(t_token **head, t_token *node)
{
	t_token	*cur;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	node->prev = cur;
}

void	remove_token(t_token **head, t_token *t)
{
	if (!head || !*head || !t)
		return ;
	if (t->prev)
		t->prev->next = t->next;
	else
		*head = t->next;
	if (t->next)
		t->next->prev = t->prev;
	free(t->str);
	free(t);
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->str)
			free(tok->str);
		if (tok->str_backup)
			free(tok->str_backup);
		free(tok);
		tok = tmp;
	}
}

void	join_tokens(t_token *tokens)
{
	t_token	*cur;
	t_token	*next;
	char	*joined;
	char	*left;
	char	*right;

	cur = tokens;
	while (cur && cur->next)
	{
		if (cur->next->join)
		{
			next = cur->next;
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
			continue ;
		}
		cur = cur->next;
	}
}
