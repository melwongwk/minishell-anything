/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:06:13 by melwong           #+#    #+#             */
/*   Updated: 2026/01/07 21:06:13 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	unquoted_len(char *s, int i, int *end)
{
	int	len;
	int	state;

	len = 0;
	state = DEFAULT;
	while (s[i])
	{
		if (state == DEFAULT && (is_space(s[i]) || s[i] == '|'))
			break ;
		if (s[i] == '\'' && state == DEFAULT)
			state = SQUOTE;
		else if (s[i] == '\'' && state == SQUOTE)
			state = DEFAULT;
		else if (s[i] == '"' && state == DEFAULT)
			state = DQUOTE;
		else if (s[i] == '"' && state == DQUOTE)
			state = DEFAULT;
		else
			len++;
		i++;
	}
	*end = i;
	return (len);
}

static int	detect_pure_quote(char *s, int start, int end)
{
	int	i;

	if (s[start] == '\'')
	{
		i = start + 1;
		while (i < end && s[i] != '\'')
			i++;
		if (i + 1 == end)
			return (SQUOTE);
	}
	if (s[start] == '"')
	{
		i = start + 1;
		while (i < end && s[i] != '"')
			i++;
		if (i + 1 == end)
			return (DQUOTE);
	}
	return (DEFAULT);
}

static void	fill_unquoted(char *s, int start, int end, char *dst)
{
	int	i;
	int	j;
	int	state;

	i = start;
	j = 0;
	state = DEFAULT;
	while (i < end)
	{
		if (s[i] == '\'' && state == DEFAULT)
			state = SQUOTE;
		else if (s[i] == '\'' && state == SQUOTE)
			state = DEFAULT;
		else if (s[i] == '"' && state == DEFAULT)
			state = DQUOTE;
		else if (s[i] == '"' && state == DQUOTE)
			state = DEFAULT;
		else
			dst[j++] = s[i];
		i++;
	}
	dst[j] = '\0';
}

static char	*extract_word(char *s, int *i, int *status)
{
	int		start;
	int		end;
	int		len;
	char	*word;

	start = *i;
	len = unquoted_len(s, start, &end);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	fill_unquoted(s, start, end, word);
	*status = detect_pure_quote(s, start, end);
	*i = end;
	return (word);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;
	char	*var;
	int		status;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
		{
			i++;
			continue ;
		}
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
		if (input[i] == '$')
		{
			var = extract_var(input, &i);
			token_append(&tokens, token_new(var, VAR, DEFAULT));
			free(var);
			continue ;
		}
		word = extract_word(input, &i, &status);
		if (*word)
			token_append(&tokens, token_new(word, WORD, status));
		free(word);
	}
	return (tokens);
}
