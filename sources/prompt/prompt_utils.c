/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:04:01 by melwong           #+#    #+#             */
/*   Updated: 2026/01/17 23:04:01 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_content(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

t_data	*init_prompt_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = dup_envp(envp);
	data->interactive = true;
	data->heredoc_interrupted = false;
	set_env_var(data, "?", "0");
	return (data);
}

int	parse_and_prepare(t_data *data)
{
	data->token = lexer(data->user_input);
	if (!data->token)
	{
		if (has_content(data->user_input))
			printf("minishell: syntax error: unclosed quote\n");
		free(data->user_input);
		return (1);
	}
	if (!check_syntax(data->token))
	{
		printf("syntax error\n");
		free_tokens(data->token);
		free(data->user_input);
		data->token = NULL;
		data->user_input = NULL;
		return (1);
	}
	expand_tokens(data->token, data->env,
		ft_atoi(get_env_var_value(data->env, "?")));
	join_tokens(data->token);
	data->cmd = parse_commands(data->token);
	handle_heredocs(data->cmd, data->env,
		ft_atoi(get_env_var_value(data->env, "?")), data);
	return (0);
}
