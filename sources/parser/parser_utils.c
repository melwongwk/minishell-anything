/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:49:42 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 15:59:58 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*cmd_new(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->io_fds = ft_calloc(1, sizeof(t_io_fds));
	//incluse initialise
	if (!cmd->io_fds)
	{
		free(cmd);
		return (NULL);
	}
	/* initialize fds to -1 to indicate "not set" */
	cmd->io_fds->fd_in = -1;
	cmd->io_fds->fd_out = -1;
	cmd->io_fds->stdin_backup = -1;
	cmd->io_fds->stdout_backup = -1;
	cmd->io_fds->heredoc_fd = -1;
	cmd->pipe_output = false;
	return (cmd);
}

char	*env_get(char **envp, const char *key)
{
	size_t	key_len;
	int		i;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
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
