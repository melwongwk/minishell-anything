/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:11 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 16:35:45 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

void	free_data(t_data *data, int clear_history)
{
	if (data && data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		clear_token(data);
	if (data && data->cmd)
		clear_cmd(data);
	if (clear_history == true)
	{
		if (data && data->working_dir)
			free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env)
			free_str_tab(data->env);
		rl_clear_history();
	}
}

void	close_fds(t_command *cmd, bool close_backup)
{
	while (cmd)
	{
		if (cmd->io_fds->fd_in != -1)
			close(cmd->io_fds->fd_in);
		if (cmd->io_fds->fd_out != -1)
			close(cmd->io_fds->fd_out);
		if (close_backup)
			restore_io(cmd->io_fds);
		cmd = cmd->next;
	}
}

void	free_ptr(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free_ptr(tab[i]);
			tab[i] = NULL;
		}
		free (tab);
		tab = NULL;
	}
}
