/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:03:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/20 17:56:28 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
		free(data);
	}
	exit(exit_code);
}

void	clear_cmd(t_data *data)
{
	t_command	*next;
	t_command	*current;

	current = data->cmd;
	while (current)
	{
		if (current->args)
			free_str_tab(current->args);
		if (current->path)
			free_ptr(current->path);
		if (current->io_fds)
			free_io(current->io_fds);
		next = current->next;
		free(current);
		current = next;
	}
}

void	clear_token(t_data *data)
{
	t_token	*next;
	t_token	*current;

	current = data->token;
	while (current)
	{
		if (current->str)
			free_ptr(current->str);
		if (current->str_backup)
			free_ptr(current->str_backup);
		next = current->next;
		free(current);
		current = next;
	}
}

void	set_exit_status(t_data *data, int ret)
{
	char	*exit_str;

	exit_str = ft_itoa(ret);
	set_env_var(data, "?", exit_str);
	free(exit_str);
}
