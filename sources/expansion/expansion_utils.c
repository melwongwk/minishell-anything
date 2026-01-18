/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 07:05:02 by melwong           #+#    #+#             */
/*   Updated: 2026/01/18 07:05:02 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(char *s, char **envp, int last_status)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(s);
	while (ft_strchr(res, '$'))
	{
		tmp = expand_one_var(res, envp, last_status);
		if (!tmp || !ft_strcmp(tmp, res))
		{
			free(tmp);
			break ;
		}
		free(res);
		res = tmp;
	}
	return (res);
}

static void	free_words(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

static void	insert_split_tokens(t_token *token, char **words)
{
	t_token	*current;
	t_token	*new_token;
	int		i;

	current = token;
	i = 1;
	while (words[i])
	{
		new_token = token_new(words[i], WORD, DEFAULT);
		if (!new_token)
			break ;
		new_token->next = current->next;
		if (current->next)
			current->next->prev = new_token;
		new_token->prev = current;
		current->next = new_token;
		current = new_token;
		i++;
	}
}

void	split_token_on_whitespace(t_token *token)
{
	char	**words;

	words = ft_split_charset(token->str, WHITESPACE);
	if (!words || !words[0])
	{
		free(words);
		return ;
	}
	free(token->str);
	token->str = ft_strdup(words[0]);
	insert_split_tokens(token, words);
	free_words(words);
}

int	find_dollar(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	return (i);
}
