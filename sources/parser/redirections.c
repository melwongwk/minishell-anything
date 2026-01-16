/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:55:33 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 16:47:44 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

static char	**arr_append(char **arr, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	len = arr_len(arr);
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (arr);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

static bool	*bool_arr_append(bool *arr, bool val, int len)
{
	bool	*new_arr;
	int		i;

	new_arr = malloc(sizeof(bool) * (len + 1));
	if (!new_arr)
		return (arr);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = val;
	free(arr);
	return (new_arr);
}

void	handle_redir_token(t_command *cmd, t_token **tok)
{
	t_token	*cur;
	t_token	*delim;
	char	*joined;
	char	*tmp;
	int		out_len;
	bool	has_output;

	cur = (*tok)->next;
	while (cur && cur->type != WORD && cur->type != VAR)
		cur = cur->next;
	if (!cur)
	{
		*tok = (*tok)->next;
		return ;
	}
	delim = cur;
	joined = ft_strdup(cur->str);
	cur = cur->next;
	while (cur && cur->join)
	{
		tmp = joined;
		joined = ft_strjoin(tmp, cur->str);
		free(tmp);
		cur = cur->next;
	}
	has_output = (cmd->io_fds->outfiles != NULL || cmd->io_fds->outfile != NULL);
	if ((*tok)->type == INPUT)
	{
		if (!has_output)
			cmd->io_fds->input_first = true;
		cmd->io_fds->infiles = arr_append(cmd->io_fds->infiles, joined);
		free_ptr(cmd->io_fds->infile);
		cmd->io_fds->infile = joined;
	}
	else if ((*tok)->type == TRUNC)
	{
		out_len = arr_len(cmd->io_fds->outfiles);
		cmd->io_fds->outfiles = arr_append(cmd->io_fds->outfiles, joined);
		cmd->io_fds->out_append = bool_arr_append(cmd->io_fds->out_append,
				false, out_len);
		free_ptr(cmd->io_fds->outfile);
		cmd->io_fds->outfile = joined;
		cmd->io_fds->append = false;
	}
	else if ((*tok)->type == APPEND)
	{
		out_len = arr_len(cmd->io_fds->outfiles);
		cmd->io_fds->outfiles = arr_append(cmd->io_fds->outfiles, joined);
		cmd->io_fds->out_append = bool_arr_append(cmd->io_fds->out_append,
				true, out_len);
		free_ptr(cmd->io_fds->outfile);
		cmd->io_fds->outfile = joined;
		cmd->io_fds->append = true;
	}
	else if ((*tok)->type == HEREDOC)
	{
		if (!has_output)
			cmd->io_fds->input_first = true;
		free_ptr(cmd->io_fds->heredoc_delimiter);
		cmd->io_fds->heredoc_delimiter = joined;
		cmd->io_fds->heredoc_quotes = (delim->status != DEFAULT);
	}
	*tok = cur;
}
