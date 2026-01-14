/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:03:46 by hho-jia-          #+#    #+#             */
/*   Updated: 2026/01/14 14:28:07 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_strs(char *s1, char *s2)
{
	char	*temp;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	temp = s1;
	s1 = ft_strjoin(s1, s2);
	free(temp);
	return (s1);
}

static int	check_exportunset(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	errcmd_msg(char *cmd, char *detail, char *err_msg, int err_no)
{
	char	*msg;
	int		err_bool;

	err_bool = 0;
	err_bool = check_exportunset(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (err_bool)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, detail);
		if (err_bool)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err_no);
}
