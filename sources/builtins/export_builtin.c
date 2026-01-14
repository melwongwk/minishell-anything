/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:26 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 17:01:43 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_builtin(t_data *data, char **args)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;
	char	*equals;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		equals = ft_strchr(args[i], '=');
		if (equals)
		{
			key = ft_strndup(args[i], equals - args[i]);
			value = ft_strdup(equals + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}
		if (!is_valid_env_var_key(key))
		{
			ret = errcmd_msg("export", args[i],
					"not a valid identifier", EXIT_FAILURE);
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
		i++;
	}
	return (ret);
}
