/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:03:31 by melwong           #+#    #+#             */
/*   Updated: 2026/01/16 17:47:39 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

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
	bool	append;
	int		heredoc_fd;
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
	int					pipe_fd[2];
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
	bool		heredoc_interrupted;
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

void		run_prompt(char **envp);
void		init_signals(void);

int			is_redir(char c);
void		handle_redirection(t_token **tokens, char *input, int *i);
char		*extract_var(char *s, int *i);
bool		check_syntax(t_token *token);
void		handle_heredocs(t_command *cmds, char **envp, int last_status, t_data *data);
char		*expand_string(char *s, char **envp, int last_status);
char		**dup_envp(char **envp);

/* lexer */
t_token		*token_new(const char *s, int type, int status);
void		token_append(t_token **head, t_token *node);
void		free_tokens(t_token *tok);
void		remove_token(t_token **head, t_token *t);
void		join_tokens(t_token *tokens);
t_token		*lexer(char *input);

/* parser */
t_command	*parse_commands(t_token *tokens);
t_command	*cmd_new(void);
int			has_whitespace(char *s);
void		handle_redir_token(t_command *cmd, t_token **tok);
void		expand_commands(t_command *cmds, char **envp, int last_status);
char		*env_get(char **envp, const char *key);
void		expand_tokens(t_token *tokens, char **envp, int last_status);

// Howard
// execute folder
// execute_cmd.c
int			execute_builtin(t_data *data, t_command *cmd);
void		execute_command(t_data *data, t_command *cmd);
// execute_utils.c
int			check_command_found(t_command *cmd);
int			cmd_is_dir(char *cmd);
// execute.c
int			execute(t_data *data);
// parse_path.c
char		*get_cmd_path( t_data *data, char *cmd);
char		*find_valid_cmd_path(char *find_cmd, char **env_paths);
char		**get_paths_from_env(t_data *data);

// Redirection Folder
// file_io.c
int			restore_io(t_io_fds *io);
int			redirect_io(t_io_fds *io_fds);
int			check_infile_outfile(t_io_fds *io_fds);
int			redirect_each_cmd_io(t_io_fds *io);
// pipe.c
void		close_unused_pipe_fds(t_data *data, t_command *cmd);

// Builtin folder
// cd.c
int			cd_builtin(t_data *data, char **args);
int			echo_builtin(char **args);
int			env_builtin(t_data *data, char **args);
int			export_builtin(t_data *data, char **args);
int			pwd_builtin(t_data *data);
int			unset_builtin(t_data *data, char **args);
int			exit_builtin(t_data *data, char **args);

// Env folder
// env_utils.c
int			get_env_var_index(char **env, char *var);
char		*get_env_var_value(char **env, char *var);
int			is_valid_env_var_key(char *key);
int			ft_isalnum(int c);
// env_set.c
int			env_var_count(char **env);
char		**realloc_env_var(t_data *data, int size);
int			set_env_var(t_data *data, char *key, char *value);
int			remove_env_var(t_data *data, int var_index);

// Utils folder
// cleanup.c
void		free_io(t_io_fds *io);
void		free_data(t_data *data, int free_env);
void		close_fds(t_command *cmd, bool close_backup);
void		free_ptr(char *str);
void		free_str_tab(char **tab);
// error.c
int			errcmd_msg(char *cmd, char *detail, char *err_msg, int err_no);
// exit.c
void		exit_shell(t_data *data, int exit_code);
void		clear_cmd(t_data *data);
void		clear_token(t_data *data);
void		set_exit_status(t_data *data, int ret);
// utils.c
int			ft_atoi_long(const char *str, bool *error);

#endif
