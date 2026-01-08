/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:14:32 by melwong           #+#    #+#             */
/*   Updated: 2026/01/07 08:14:32 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


/*
 * Create a new token. copies `s` into both str and str_backup.
 * `type` should be one of the enum token types from the header.
 * `status` should be DEFAULT / SQUOTE / DQUOTE as appropriate.
 */
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

/*
 * Append `node` to the end of the token list pointed to by *head.
 * If *head is NULL the node becomes the first element.
 */
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

/*
 * Debug print for tokens. Shows type, status, join and var flag,
 * and the token string (or "(null)" if missing).
 */
void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("T(type=%d,status=%d,join=%d,var=%d) '%s'\n",
			tok->type,
			tok->status,
			(int)tok->join,
			(int)tok->var_exists,
			tok->str ? tok->str : "(null)");
		tok = tok->next;
	}
}

/*
 * Free all tokens (str and str_backup included).
 */
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


