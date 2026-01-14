/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:03:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 14:29:22 by hho-jia-         ###   ########.fr       */
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
		if (current->command)
			free_ptr(current->command);
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
