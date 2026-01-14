/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:17 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 12:05:18 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_builtin(t_data *data, char **args)
{
	int	i;
	int	var_index;

	i = 0;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
			return (errcmd_msg("unset",
					args[i], "not a valid identifier", EXIT_FAILURE));
		else if (ft_strchr(args[i], '=') != NULL)
			return (errcmd_msg("unset",
					args[i], "invalid parameter name", EXIT_FAILURE));
		else
		{
			var_index = get_env_var_index(data->env, args[i]);
			if (var_index != -1)
			{
				remove_env_var(data, var_index);
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	return (EXIT_FAILURE);
}
