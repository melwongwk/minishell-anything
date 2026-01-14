/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:26 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/13 12:05:27 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_builtin(t_data *data, char **args)
{
	int		i;
	int		ret;
	char	**temp;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
			return (errcmd_msg("export",
					args[i], "not a valid identifier", EXIT_FAILURE));
		else if (ft_strchr(args[i], '='))
		{
			temp = ft_split(args[i], '=');
			if (!temp)
				return (EXIT_FAILURE);
			set_env_var(data, temp[0], temp[1]);
			free_str_tab(temp);
		}
		i++;
	}
	return (0);
}
