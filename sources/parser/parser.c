/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:49:35 by melwong           #+#    #+#             */
/*   Updated: 2026/01/08 22:49:35 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static int	count_args(t_token *tok)
{
	int	count = 0;

	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD || tok->type == VAR)
			count++;
		tok = tok->next;
	}
	return (count);
}

static void	fill_args(t_command *cmd, t_token **tok)
{
	int		i;
	int		argc;
	t_token	*tmp;

	tmp = *tok;
	argc = count_args(tmp);
	cmd->args = ft_calloc(argc + 1, sizeof(char *));
	i = 0;

	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INPUT || tmp->type == TRUNC
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			handle_redir_token(cmd, &tmp);
			continue ;
		}
		if (tmp->type == WORD || tmp->type == VAR)
		{
			cmd->args[i++] = ft_strdup(tmp->str);
			if (!cmd->command)
				cmd->command = cmd->args[0];
		}
		tmp = tmp->next;
	}
	*tok = tmp;
}

t_command	*parse_commands(t_token *tokens)
{
	t_command	*cmds = NULL;
	t_command	*last = NULL;
	t_command	*cmd;

	while (tokens)
	{
		cmd = cmd_new();
		fill_args(cmd, &tokens);

		if (tokens && tokens->type == PIPE)
		{
			cmd->pipe_output = true;
			tokens = tokens->next;
		}

		if (!cmds)
			cmds = cmd;
		else
		{
			last->next = cmd;
			cmd->prev = last;
		}
		last = cmd;
	}
	return (cmds);
}
