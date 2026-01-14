/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:10 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 17:01:22 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_count(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

char	**realloc_env_var(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size && data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	free(data->env);
	return (new_env);
}

int	set_env_var(t_data *data, char *key, char *value)
{
	int		var_index;
	char	*temp;

	var_index = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	temp = ft_strjoin("=", value);
	if (!temp)
		return (0);
	if (var_index != -1)
	{
		free_ptr(data->env[var_index]);
		data->env[var_index] = ft_strjoin(key, temp);
	}
	else
	{
		var_index = env_var_count(data->env);
		data->env = realloc_env_var(data, var_index + 1);
		if (data->env == NULL)
			return (free_ptr(temp), 0);
		data->env[var_index] = ft_strjoin(key, temp);
	}
	free_ptr(temp);
	return (1);
}

int	remove_env_var(t_data *data, int var_index)
{
	if (var_index >= env_var_count(data->env) || var_index < 0)
		return (0);
	free_ptr(data->env[var_index]);
	while (data->env[var_index + 1])
	{
		data->env[var_index] = data->env[var_index + 1];
		var_index++;
	}
	data->env[var_index] = NULL;
	data->env = realloc_env_var(data, var_index);
	if (data->env == NULL)
		return (0);
	return (1);
}
