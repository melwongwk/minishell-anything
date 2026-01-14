/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:06 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 12:05:06 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)))
		{
			free_ptr(temp);
			return (i);
		}
		i++;
	}
	free_ptr(temp);
	return (-1);
}

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)))
		{
			free_ptr(temp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(temp);
	return (NULL);
}

int	is_valid_env_var_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (c);
	return (0);
}
