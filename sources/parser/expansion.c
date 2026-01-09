/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 07:13:45 by melwong           #+#    #+#             */
/*   Updated: 2026/01/09 07:13:59 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static char	*expand_one_var(char *s, t_env *env, int last_status)
{
	int		i;
	char	*name;
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*tmp;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (!s[i])
		return (ft_strdup(s));

	if (s[i + 1] == '?')
	{
		value = ft_itoa(last_status);
		name = ft_strdup("$?");
	}
	else
	{
		int start = i + 1;
		int len = 0;
		while (ft_isalnum(s[start + len]) || s[start + len] == '_')
			len++;
		name = ft_strndup(s + i, len + 1);
		value = env_get(env, name + 1);
	}

	if (!value)
		value = "";

	prefix = ft_strndup(s, i);
	suffix = ft_strdup(s + i + ft_strlen(name));

	tmp = ft_strjoin(prefix, value);
	free(prefix);
	tmp = ft_strjoin_free(tmp, suffix, 1);

	free(name);
	return (tmp);
}

char	*expand_string(char *s, t_env *env, int last_status)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(s);
	while (ft_strchr(res, '$'))
	{
		tmp = expand_one_var(res, env, last_status);
		free(res);
		res = tmp;
	}
	return (res);
}

void	expand_command(t_command *cmd, t_env *env, int last_status)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		cmd->args[i] = expand_string(cmd->args[i], env, last_status);
		i++;
	}
}

void	expand_redirections(t_command *cmd, t_env *env, int last_status)
{
	if (cmd->io_fds->infile)
		cmd->io_fds->infile =
			expand_string(cmd->io_fds->infile, env, last_status);

	if (cmd->io_fds->outfile)
		cmd->io_fds->outfile =
			expand_string(cmd->io_fds->outfile, env, last_status);

	if (cmd->io_fds->heredoc_delimiter
		&& !cmd->io_fds->heredoc_quotes)
		cmd->io_fds->heredoc_delimiter =
			expand_string(cmd->io_fds->heredoc_delimiter, env, last_status);
}

void	expand_commands(t_command *cmds, t_env *env, int last_status)
{
	while (cmds)
	{
		expand_command(cmds, env, last_status);
		expand_redirections(cmds, env, last_status);
		cmds = cmds->next;
	}
}
