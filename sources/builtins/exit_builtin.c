/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/20 18:41:04 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_exit_arg(char *arg)
{
	unsigned long long	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	get_exit_code(t_data *data, char *arg, bool *error)
{
	char	*exit_str;
	int		code;

	if (error)
		*error = false;
	if (!arg)
	{
		exit_str = get_env_var_value(data->env, "?");
		if (exit_str)
			return (ft_atoi(exit_str));
		return (0);
	}
	if (!is_valid_exit_arg(arg))
		*error = true;
	code = ft_atoi_long(arg, error);
	return (code % 256);
}

int	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (0);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (1);
	return (0);
}

static void	exit_builtin_helper(t_data *data, int *exit_code)
{
	if (get_env_var_value(data->env, "?"))
		*exit_code = ft_atoi(get_env_var_value(data->env, "?"));
	else
		*exit_code = 0;
}

int	exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	int		quiet;
	bool	error;

	error = false;
	quiet = is_quiet_mode(data);
	if (!quiet)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args || !args[1])
	{
		exit_builtin_helper(data, &exit_code);
	}
	else
	{
		exit_code = get_exit_code(data, args[1], &error);
		if (error)
			exit_code = errcmd_msg("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errcmd_msg("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
