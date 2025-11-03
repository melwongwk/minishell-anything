/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:03:31 by melwong           #+#    #+#             */
/*   Updated: 2025/10/06 19:08:37 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}					t_env;

void	run_prompt(t_env *env);
t_env	*init_env(char **envp);
void	free_env(t_env *env);
void	init_signals(void);

void	print_env(t_env *env);

#endif
