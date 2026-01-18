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
	free(t->str_backup);
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
