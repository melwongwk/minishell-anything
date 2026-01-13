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
	char		*line;
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.env = env_list_to_array(env);
	data.interactive = true;
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
		data.user_input = line;
		data.token = lexer(line);
		if (!check_syntax(data.token))
		{
			printf("Syntax error\n");
			free(line);
			free_tokens(data.token);
			continue ;
		}
		expand_tokens(data.token, data.env, 0);
		join_tokens(data.token);
		data.cmd = parse_commands(data.token);
		handle_heredocs(data.cmd, data.env, 0);
		print_commands(data.cmd);
		free_commands(data.cmd);
		free_tokens(data.token);
		free(line);
	}
	free_split(data.env);
}
