/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:07:54 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 12:59:47 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	char	*temp;
	int		i;

	envp = ft_calloc(env_count(env) + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			temp = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(temp, env->value);
			free(temp);
		}
		else
			envp[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
