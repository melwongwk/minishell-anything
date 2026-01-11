/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2025/10/06 20:04:25 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

void	run_prompt(t_env *env)
{
	char	*line;
	t_token *tokens;
	t_command *cmds;

	while (1)
	{
		line = readline("minishell:~$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		if (!check_syntax(tokens))
		{
			printf("Syntax error\n");
			free(line);
			free_tokens(tokens);
			continue ;
		}
		expand_tokens(tokens, env, 0);
		join_tokens(tokens);
		cmds = parse_commands(tokens);
		handle_heredocs(cmds, env, 0);
		print_commands(cmds);
		free_commands(cmds);
		free_tokens(tokens);
		free(line);
	}
}
