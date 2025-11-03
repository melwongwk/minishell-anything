/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:07:54 by melwong           #+#    #+#             */
/*   Updated: 2025/10/07 11:12:09 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static t_env	*env_new(const char *entry)
{
	char	*equals;
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equals = ft_strchr(entry, '=');
	if (!equals)
	{
		new_node->key = ft_strdup(entry);
		new_node->value = NULL;
	}
	else
	{
		new_node->key = ft_strndup(entry, equals - entry);
		new_node->value = ft_strdup(equals + 1);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*cur;
	t_env	*temp;
	int		i;

	head = NULL;
	cur = NULL;
	i = 0;
	while (envp[i])
	{
		temp = env_new(envp[i]);
		if (!temp)
		{
			free_env(head);
			exit(EXIT_FAILURE);
		}
		if (!head)
			head = temp;
		else
			cur->next = temp;
		cur = temp;
		i++;
	}
	return (head);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		else
			ft_printf("%s\n", env->key);
		env = env->next;
	}
}
