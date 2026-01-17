/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:34 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/17 12:05:21 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
		return (errcmd_msg("env", NULL, "too many arguments", 2));
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "?=", 2) != 0)
			ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
