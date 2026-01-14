/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 07:03:12 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 12:59:52 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->io_fds)
		{
			free(cmd->io_fds->infile);
			free(cmd->io_fds->outfile);
			free(cmd->io_fds->heredoc_delimiter);
			free(cmd->io_fds);
		}
		free(cmd);
		cmd = next;
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
