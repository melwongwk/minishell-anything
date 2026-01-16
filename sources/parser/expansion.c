/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 07:13:45 by melwong           #+#    #+#             */
/*   Updated: 2026/01/15 19:17:47 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_one_var(char *s, char **envp, int last_status)
{
	int		i;
	char	*name;
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*final;
	int		start;
	int		len;

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
	else if (!s[i + 1] || (!ft_isalnum(s[i + 1]) && s[i + 1] != '_'))
	{
		return (ft_strdup(s));
	}
	else
	{
		start = i + 1;
		len = 0;
		while (ft_isalnum(s[start + len]) || s[start + len] == '_')
			len++;
		name = ft_strndup(s + i, len + 1);
		value = env_get(envp, name + 1);
	}
	if (!value)
		value = "";
	prefix = ft_strndup(s, i);
	suffix = ft_strdup(s + i + ft_strlen(name));
	tmp = ft_strjoin(prefix, value);
	final = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	if (!ft_strcmp(name, "$?"))
		free(value);
	free(name);
	return (final);
}

char	*expand_string(char *s, char **envp, int last_status)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(s);
	while (ft_strchr(res, '$'))
	{
		tmp = expand_one_var(res, envp, last_status);
		if (!tmp || !ft_strcmp(tmp, res))
		{
			free(tmp);
			break ;
		}
		free(res);
		res = tmp;
	}
	return (res);
}

static void	split_token_on_whitespace(t_token *token)
{
	char	**words;
	int		i;
	t_token	*new_token;
	t_token	*current;

	words = ft_split_charset(token->str, " \t\n");
	if (!words || !words[0])
	{
		free(words);
		return ;
	}
	free(token->str);
	token->str = ft_strdup(words[0]);
	current = token;
	i = 1;
	while (words[i])
	{
		new_token = token_new(words[i], WORD, DEFAULT);
		if (!new_token)
			break ;
		new_token->next = current->next;
		if (current->next)
			current->next->prev = new_token;
		new_token->prev = current;
		current->next = new_token;
		current = new_token;
		i++;
	}
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

void	expand_command(t_command *cmd, char **envp, int last_status)
{
	int		i;
	char	*old_arg;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		old_arg = cmd->args[i];
		cmd->args[i] = expand_string(cmd->args[i], envp, last_status);
		free(old_arg);
		i++;
	}
}

void	expand_redirections(t_command *cmd, char **envp, int last_status)
{
	char	*old;

	if (cmd->io_fds->infile)
	{
		old = cmd->io_fds->infile;
		cmd->io_fds->infile = expand_string(old, envp, last_status);
		free(old);
	}
	if (cmd->io_fds->outfile)
	{
		old = cmd->io_fds->outfile;
		cmd->io_fds->outfile = expand_string(old, envp, last_status);
		free(old);
	}
	if (cmd->io_fds->heredoc_delimiter && !cmd->io_fds->heredoc_quotes)
	{
		old = cmd->io_fds->heredoc_delimiter;
		cmd->io_fds->heredoc_delimiter = expand_string(old, envp, last_status);
		free(old);
	}
}

void	expand_commands(t_command *cmds, char **envp, int last_status)
{
	while (cmds)
	{
		expand_command(cmds, envp, last_status);
		expand_redirections(cmds, envp, last_status);
		cmds = cmds->next;
	}
}

void	expand_tokens(t_token *tokens, char **envp, int last_status)
{
	t_token	*t;
	t_token	*next;
	char	*expanded;

	t = tokens;
	while (t)
	{
		next = t->next;
		if ((t->type == WORD || t->type == VAR) && t->str)
		{
			if (t->status != SQUOTE)
			{
				expanded = expand_string(t->str, envp, last_status);
				free(t->str);
				t->str = expanded;
			}
			t->type = WORD;
			t->status = DEFAULT;
			if (!t->str || !*t->str)
			{
				remove_token(&tokens, t);
				t = next;
				continue ;
			}
		}
		if (t->status == DEFAULT && t->type == WORD
			&& t->str && has_whitespace(t->str))
			split_token_on_whitespace(t);
		t = t->next;
	}
}
