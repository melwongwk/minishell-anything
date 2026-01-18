/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 07:42:34 by melwong           #+#    #+#             */
/*   Updated: 2026/01/18 07:42:34 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_dollar(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	return (i);
}

static char	*get_variable_name(char *s, int i)
{
	int		start;
	int		len;

	if (s[i + 1] == '?')
		return (ft_strdup("$?"));
	if (!s[i + 1] || (!ft_isalnum(s[i + 1]) && s[i + 1] != '_'))
		return (NULL);
	start = i + 1;
	len = 0;
	while (ft_isalnum(s[start + len]) || s[start + len] == '_')
		len++;
	return (ft_strndup(s + i, len + 1));
}

static char	*get_variable_value(char **envp, char *name, int last_status)
{
	if (ft_strcmp(name, "$?") == 0)
		return (ft_itoa(last_status));
	return (env_get(envp, name + 1));
}

static char	*build_expanded(char *s, int i, char *name, char *value)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*final;

	prefix = ft_strndup(s, i);
	suffix = ft_strdup(s + i + ft_strlen(name));
	tmp = ft_strjoin(prefix, value);
	final = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	return (final);
}

char	*expand_one_var(char *s, char **envp, int last_status)
{
	int		i;
	char	*name;
	char	*value;
	char	*result;

	i = find_dollar(s);
	if (!s[i])
		return (ft_strdup(s));
	name = get_variable_name(s, i);
	if (!name)
		return (ft_strdup(s));
	value = get_variable_value(envp, name, last_status);
	if (!value)
		return (ft_strdup(s));
	result = build_expanded(s, i, name, value);
	if (!ft_strcmp(name, "$?"))
		free(value);
	free(name);
	return (result);
}
