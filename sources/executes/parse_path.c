/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:40 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 12:04:40 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_valid_cmd_path(char *find_cmd, char **env_paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], find_cmd);
		if (!cmd_path)
		{
			errcmd_msg("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (get_env_var_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_value(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

char	*get_cmd_path( t_data *data, char *cmd)
{
	char	**env_paths;
	char	*find_cmd;
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	find_cmd = ft_strjoin("/", cmd);
	if (!find_cmd)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(find_cmd, env_paths);
	if (!cmd_path)
	{
		free_ptr(find_cmd);
		free_str_tab(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
