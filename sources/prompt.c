/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 19:45:35 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal = 0;

static void	sig_int_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&sa_quit, sizeof(sa_int));
	sa_int.sa_handler = sig_int_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	run_prompt(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->env = dup_envp(envp);
	data->interactive = true;
	data->heredoc_interrupted = false;
	set_env_var(data, "?", "0");
	while (1)
	{
		data->user_input = readline("minishell:~$ ");
		if (!data->user_input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
		{
			free(data->user_input);
			data->user_input = NULL;
			g_signal = 0;
			continue ;
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
		expand_tokens(data->token, data->env, ft_atoi(get_env_var_value(data->env, "?")));
		join_tokens(data->token);
		data->cmd = parse_commands(data->token);
		handle_heredocs(data->cmd, data->env, ft_atoi(get_env_var_value(data->env, "?")), data);
		if (data->heredoc_interrupted)
		{
			free_data(data, false);
			continue ;
		}
		execute(data);
		free_data(data, false); // must use with execute together to clean the data
	}
	rl_clear_history();
}
