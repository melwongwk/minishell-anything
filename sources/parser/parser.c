/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:49:35 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 13:00:35 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == INPUT || tok->type == TRUNC
			|| tok->type == APPEND || tok->type == HEREDOC)
		{
			tok = tok->next;
			while (tok && tok->join)
				tok = tok->next;
			if (tok)
				tok = tok->next;
			else
				tok = NULL;
			continue ;
		}
		if (tok->type == WORD)
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
		if (tmp->type == WORD)
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
	t_command	*cmds;
	t_command	*last;
	t_command	*cmd;

	*cmds = NULL;
	*last = NULL;
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
