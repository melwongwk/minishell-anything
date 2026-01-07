/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:10:46 by melwong           #+#    #+#             */
/*   Updated: 2025/10/06 20:04:25 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

/* static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
} */

void	run_prompt(t_env *env)
{
	char	*line;
//	char	**argv;

	(void)env;
	while (1)
	{
		line = readline("minishell:~$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
//		printf("You typed: %s\n", line);
		t_token *tokens;

		tokens = lexer(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
		/* if (ft_strcmp(argv[0], "exit") == 0)
		{
			printf("exit\n");
			free_args(argv);
			free_env(env);
			exit(EXIT_SUCCESS);
		}
		else if (ft_strcmp(argv[0], "print") == 0)
		{
			if (argv && argv[0])
			{
				int i = 1;
				while (argv[i])
					printf("%s ", argv[i++]);
				printf("\n");
			}
		} */
//		free_args(argv);
	}
}
