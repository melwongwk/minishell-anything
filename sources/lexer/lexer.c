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

#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "libft.h"

static char *extract_segment(char *s, int *i, int *status)
{
    int start = *i;

    if (s[*i] == '\'' || s[*i] == '"')
    {
        char quote = s[*i];
        *status = (quote == '\'') ? SQUOTE : DQUOTE;
        (*i)++;
        start = *i;
        while (s[*i] && s[*i] != quote)
            (*i)++;

        char *seg = ft_strndup(s + start, *i - start);
        if (s[*i] == quote)
            (*i)++;
        return seg;
    }
    *status = DEFAULT;
    while (s[*i]
        && !ft_isspace(s[*i])
        && s[*i] != '|'
        && !is_redir(s[*i])
        && s[*i] != '\''
        && s[*i] != '"'
        && s[*i] != '$')
        (*i)++;
    return ft_strndup(s + start, *i - start);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;
	char	*var;
	int		status;
	int		start;
	t_token	*new;
	bool	prev_was_word;

	tokens = NULL;
	i = 0;
	prev_was_word = false;
	while (input[i])
	{
		if (ft_isspace(input[i]))
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
			new = token_new(var, VAR, DEFAULT);
			if (prev_was_word)
				new->join = 1;
			token_append(&tokens, new);
			prev_was_word = true;
			free(var);
			continue ;
		}
		else
		{
			start = i;
			word = extract_segment(input, &i, &status);
			if (*word)
			{
				new = token_new(word, WORD, status);
				if (tokens && start > 0 && !ft_isspace(input[start - 1]))
					new->join = 1;
				token_append(&tokens, new);
				prev_was_word = true;
			}
			free(word);
		}
	}
	return (tokens);
}
