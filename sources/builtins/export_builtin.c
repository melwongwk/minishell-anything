/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:26 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/15 18:41:55 by hho-jia-         ###   ########.fr       */
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

int	export_builtin(t_data *data, char **args)
{
	int		i;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (handle_export_arg(data, args[i]) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
