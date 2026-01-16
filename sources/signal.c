/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:20:27 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 13:53:39 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile static sig_atomic_t	g_signal = 0;

static void	sig_int_handler(int sig)
{
	g_signal = sig;
	(void)write(STDOUT_FILENO, "\n", 1);
}

void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
    ft_bzero(&sa_quit, sizeof(sa_quit));
    sa_int.sa_handler = sig_int_handler;
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
