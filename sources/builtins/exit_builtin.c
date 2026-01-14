/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:05:31 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 13:56:09 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(t_data *data, char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (data->g_last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
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

int	exit_builtin(t_data *data, char **args)
{
	int	exit_code;
	int	quiet;
	bool	error;

	quiet = is_quiet_mode(data);
	if (!quiet || data->interactive)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!args || !args[1])
		exit_code = data->g_last_exit_code;
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
