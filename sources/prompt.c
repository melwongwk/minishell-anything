/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 16:54:41 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_prompt(t_env *env)
{
	char		*line;
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.env = env_list_to_array(env);
	data.interactive = true;
	set_env_var(&data, "?", "0");
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
		if (!data.token)
		{
			printf("minishell: syntax error: unclosed quote\n");
			free(line);
			continue ;
		}
		if (!check_syntax(data.token))
		{
			printf("Syntax error\n");
			free(line);
			free_tokens(data.token);
			data.token = NULL;
			continue ;
		}
		expand_tokens(data.token, data.env, 0);
		join_tokens(data.token);
		data.cmd = parse_commands(data.token);
		handle_heredocs(data.cmd, data.env, 0);
		execute(&data);
		free_commands(data.cmd);
		free_tokens(data.token);
		free(line);
	}
	free_split(data.env);
}
