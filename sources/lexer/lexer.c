/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:06:13 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 13:00:56 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_token **tokens, int *i)
{
	token_append(tokens, token_new("|", PIPE, DEFAULT));
	(*i)++;
}

static bool	handle_special_tokens(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		handle_pipe(tokens, i);
		return (true);
	}
	if (is_redir(input[*i]))
	{
		handle_redirection(tokens, input, i);
		return (true);
	}
	return (false);
}

static void	init_lexer_variables(t_token **tokens, int *i, bool *had_space)
{
	*tokens = NULL;
	*i = 0;
	*had_space = true;
}

static void	process_token(char *input, int *i,
				bool *had_space, t_token **tokens)
{
	t_token	*new;

	new = parse_token(input, i);
	if (new)
	{
		if (!*had_space)
			new->join = true;
		token_append(tokens, new);
	}
	*had_space = false;
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	bool	had_space;

	init_lexer_variables(&tokens, &i, &had_space);
	while (input[i])
	{
		skip_whitespace(input, &i, &had_space);
		if (!input[i])
			break ;
		if (handle_special_tokens(input, &i, &tokens))
		{
			had_space = true;
			continue ;
		}
		process_token(input, &i, &had_space, &tokens);
	}
	return (tokens);
}
