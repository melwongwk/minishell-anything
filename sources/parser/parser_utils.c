/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:49:42 by melwong           #+#    #+#             */
/*   Updated: 2026/01/08 22:49:42 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"

t_command	*cmd_new(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->io_fds = ft_calloc(1, sizeof(t_io_fds));
	return (cmd);
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("COMMAND: %s\n", cmd->command);
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("  arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		if (cmd->io_fds->infile)
			printf("  infile: %s\n", cmd->io_fds->infile);
		if (cmd->io_fds->outfile)
			printf("  outfile: %s\n", cmd->io_fds->outfile);
		if (cmd->io_fds->heredoc_delimiter)
			printf("  heredoc: %s (quoted=%d)\n",
				cmd->io_fds->heredoc_delimiter,
				cmd->io_fds->heredoc_quotes);
		printf("  pipe_output: %d\n", cmd->pipe_output);
		printf("------\n");
		cmd = cmd->next;
	}
}
