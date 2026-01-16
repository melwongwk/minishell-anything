/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:06:13 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 15:44:24 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_segment(char *s, int *i, int *status, bool *is_var)
{
	int		start;
	char	q;
	char	*out;

	*is_var = false;
	if (s[*i] == '$')
	{
		start = (*i)++;
		if (s[*i] == '?')
			(*i)++;
		else
			while (ft_isalnum(s[*i]) || s[*i] == '_')
				(*i)++;
		*status = DEFAULT;
		*is_var = true;
		return (ft_strndup(s + start, *i - start));
	}
	if (s[*i] == '\'' || s[*i] == '"')
	{
		q = s[*i];
		if (q == '\'')
			*status = SQUOTE;
		else
			*status = DQUOTE;
		start = ++(*i);
		while (s[*i] && s[*i] != q)
			(*i)++;
		out = ft_strndup(s + start, *i - start);
		if (s[*i] == q)
			(*i)++;
		else
		{
			free(out);
			return (NULL);
		}
		return (out);
	}
	start = *i;
	*status = DEFAULT;
	while (s[*i] && !ft_isspace(s[*i]) && !is_redir(s[*i])
		&& s[*i] != '|' && s[*i] != '$' && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	return (ft_strndup(s + start, *i - start));
}

t_token	*lexer(char *input)
{
	if (!input)
		return (NULL);
	/* debug: printf("[DEBUG] lexer input: '%s'\n", input); */
	t_token	*tokens;
	int		i;
	bool	had_space;
	int		status;
	bool	is_var;
	char	*seg;
	t_token	*new;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		had_space = false;
		while (ft_isspace(input[i]))
		{
			had_space = true;
			i++;
		}
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			token_append(&tokens, token_new("|", PIPE, DEFAULT));
			i++;
			continue ;
		}
		if (is_redir(input[i]))
		{
			handle_redirection(&tokens, input, &i);
			continue ;
		}
		seg = extract_segment(input, &i, &status, &is_var);
		if (!seg)
		{
			free_tokens(tokens);
			return (NULL);
		}
		if (*seg)
		{
			if (is_var)
				new = token_new(seg, VAR, status);
			else
				new = token_new(seg, WORD, status);
			if (!had_space)
				new->join = true;
			token_append(&tokens, new);
		}
		free(seg);
	}
	return (tokens);
}
