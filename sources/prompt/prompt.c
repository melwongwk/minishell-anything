/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2026/01/17 12:05:21 by hho-jia-         ###   ########.fr       */
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

static int	read_prompt_input(t_data *data)
{
	g_signal = 0;
	data->user_input = readline("minishell:~$ ");
	if (!data->user_input)
	{
		printf("exit\n");
		return (0);
	}
	if (g_signal == SIGINT)
	{
		free(data->user_input);
		data->user_input = NULL;
		return (1);
	}
	if (*data->user_input)
		add_history(data->user_input);
	return (2);
}

int	run_prompt(char **envp)
{
	t_data	*data;
	int		status;

	data = init_prompt_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	while (1)
	{
		status = read_prompt_input(data);
		if (status == 0)
			break ;
		else if (status == 1)
			continue ;
		if (parse_and_prepare(data))
			continue ;
		if (handle_heredoc_interrupt(data))
			continue ;
		execute(data);
		free_data(data, false);
	}
	status = ft_atoi(get_env_var_value(data->env, "?"));
	free_data(data, true);
	free(data);
	return (status);
}
