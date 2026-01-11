/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 07:03:12 by melwong           #+#    #+#             */
/*   Updated: 2026/01/12 07:03:12 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
