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

# include <stdbool.h>
# include <signal.h>
# include "libft.h"

typedef struct s_token
{
	char			*str;
	char			*str_backup;
	bool			var_exists;
	int				type;
	int				status;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}			t_io_fds;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_data
{
	bool		interactive;
	t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}				t_data;

enum e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}					t_env;

void		run_prompt(t_env *env);
t_env		*init_env(char **envp);
void		free_env(t_env *env);
void		init_signals(void);

void		print_env(t_env *env);

int			is_redir(char c);
void		handle_redirection(t_token **tokens, char *input, int *i);
char		*extract_var(char *s, int *i);
bool		check_syntax(t_token *token);
void		handle_heredocs(t_command *cmds, t_env *env, int last_status);
char		*expand_string(char *s, t_env *env, int last_status);
void		free_commands(t_command *cmd);

/* lexer */
t_token		*token_new(const char *s, int type, int status);
void		token_append(t_token **head, t_token *node);
void		free_tokens(t_token *tok);
void		print_tokens(t_token *tok);
void		join_tokens(t_token *tokens);
t_token		*lexer(char *input);

/* parser */
t_command	*parse_commands(t_token *tokens);
t_command	*cmd_new(void);
void		handle_redir_token(t_command *cmd, t_token **tok);
void		free_commands(t_command *cmd);
void		print_commands(t_command *cmd);
void		expand_commands(t_command *cmds, t_env *env, int last_status);
char		*env_get(t_env *env, const char *key);
void		expand_tokens(t_token *tokens, t_env *env, int last_status);

/* env bridging */
char		**env_list_to_array(t_env *env);

#endif
