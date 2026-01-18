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

static char	*get_var_value(char *s, int i, char **envp,
						int last_status, char **name)
{
	int	start;
	int	len;

	if (s[i + 1] == '?')
	{
		*name = ft_strdup("$?");
		return (ft_itoa(last_status));
	}
	if (!s[i + 1] || (!ft_isalnum(s[i + 1]) && s[i + 1] != '_'))
		return (NULL);
	start = i + 1;
	len = 0;
	while (ft_isalnum(s[start + len]) || s[start + len] == '_')
		len++;
	*name = ft_strndup(s + i, len + 1);
	return (env_get(envp, *name + 1));
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
	value = get_var_value(s, i, envp, last_status, &name);
	if (!value)
		return (ft_strdup(s));
	if (!value)
		value = "";
	result = build_expanded(s, i, name, value);
	if (!ft_strcmp(name, "$?"))
		free(value);
	free(name);
	return (result);
}
