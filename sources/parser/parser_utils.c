/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:49:42 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 19:49:57 by hho-jia-         ###   ########.fr       */
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
	if (!cmd->io_fds)
	{
		free(cmd);
		return (NULL);
	}
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

int	has_whitespace(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}
