/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:26 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/17 16:56:53 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_export_arg(char *arg, char **key, char **value, char **equals)
{
	*equals = ft_strchr(arg, '=');
	if (*equals)
	{
		*key = ft_strndup(arg, *equals - arg);
		*value = ft_strdup(*equals + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

static int	handle_export_arg(t_data *data, char *arg)
{
	char	*key;
	char	*value;
	char	*equals;
	int		ret;

	ret = EXIT_SUCCESS;
	parse_export_arg(arg, &key, &value, &equals);
	if (!is_valid_env_var_key(key))
	{
		ret = errcmd_msg("export", arg, "not a valid identifier", EXIT_FAILURE);
		free(key);
		if (value)
			free(value);
	}
	else if (equals)
	{
		set_env_var(data, key, value);
		free(key);
		free(value);
	}
	else
		free(key);
	return (ret);
}

static void	export_builtin_helper(t_data *data, char *eachenv, int i)
{
	char	*tmp;
	char	*key;
	char	*value;
	char	*equals;

	equals = ft_strchr(data->env[i], '=');
	parse_export_arg(eachenv, &key, &value, &equals);
	tmp = ft_strjoin("declare -x ", key);
	free(key);
	key = ft_strjoin(tmp, "=\"");
	free(tmp);
	tmp = ft_strjoin(key, value);
	free(value);
	free(key);
	key = ft_strjoin(tmp, "\"");
	ft_putendl_fd(key, STDOUT_FILENO);
	free(tmp);
	free(key);
}

static int	export_env_builtin(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "?=", 2) != 0)
			export_builtin_helper(data, data->env[i], i);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_data *data, char **args)
{
	int		i;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (export_env_builtin(data));
	while (args[i])
	{
		if (handle_export_arg(data, args[i]) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
