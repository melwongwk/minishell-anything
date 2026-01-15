/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2026/01/15 18:18:28 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_prompt(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->env = dup_envp(envp);
	data->interactive = true;
	set_env_var(data, "?", "0");
	while (1)
	{
		data->user_input = readline("minishell:~$ ");
		if (!data->user_input)
		{
			printf("exit\n");
			break ;
		}
		if (*data->user_input)
			add_history(data->user_input);
		data->token = lexer(data->user_input);
		if (!data->token)
		{
			printf("minishell: syntax error: unclosed quote\n");
			free(data->user_input);
			continue ;
		}
		if (!check_syntax(data->token))
		{
			printf("syntax error\n");
			free_tokens(data->token);
			free(data->user_input);
			data->token = NULL;
			data->user_input = NULL;
			continue ;
		}
		expand_tokens(data->token, data->env, 0);
		join_tokens(data->token);
		data->cmd = parse_commands(data->token);
		handle_heredocs(data->cmd, data->env, 0);
		execute(data);
		free_data(data, false); // must use with execute together to clean the data
	}
	rl_clear_history();
}
