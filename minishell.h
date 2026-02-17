/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:16:41 by satabay           #+#    #+#             */
/*   Updated: 2026/02/17 20:27:37 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <signal.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

t_token	*lexer(char	*input);
int		handle_operator(t_token	**token_list, char *input, int i);
int		handle_word(t_token **token_list, char *input, int i);
t_token	*lexer(char	*input);
t_token	*ft_new_token(char *content, t_token_type type);
void	token_add_list(t_token **token_list, t_token *new_token);
void	free_token_list(t_token **token);
void	init_env(t_env **env_list, char **envp);
char	*get_env_value(char *name, t_env *env_list);
char	*remove_quotes(char *str);
void	expander(t_token **token_list, t_env *env_list);
char	*var_name(char *s);
char	*replace_string(char *old_str, int start, int len_name, char *new);
void	expand_token(t_token *token, t_env *env_list);
t_cmd	*new_cmd_node(void);
t_cmd	*new_cmd_node(void);
char	**join_str_array(char *arr[], char *new_str);
t_redir	*add_redirect(t_token *token, t_cmd *cmd);
t_cmd	*parse_token(t_token *token_list);
int		ft_isspace(int c);
int		skip_quotes(char *input, int i);
void	increment_shell_level(t_env *env_list);
void	expand_process(t_token *token, int *i, t_env *env_list);
void	create_default_env(t_env **env_list);
void	env_add_back(t_env **env_list, t_env *new);
t_env	*new_env_node(char *key, char *value);
void	*syntax_error(char *s);
int		redir_type_atama(int token_type);
int		word_handle(t_token *token, t_cmd *current, t_cmd **head);
int		handle_pipe(t_token *token, t_cmd **head, t_cmd **current);
int		redirection_handle(t_token **token, t_cmd *current, t_cmd **head);
int		process_token(t_token **token, t_cmd **current, t_cmd **head);
char	*get_expansion_value(char *name, t_env *env_list);
char	**env_to_array(t_env *env);
char	*find_path(char *cmd, t_env *env);
void	free_arr(char **arr);
void	executor(t_cmd *cmd, t_env *env);
char	*check_access(char **arr, char *cmd);
void	handle_child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fd);
char	*key_value(t_env *env);
void	setup_child_fds(t_cmd *cmd, int prev_fd, int *fd);
void	execute_command(t_cmd *cmd, t_env *env);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_exit(t_cmd *cmd);
void	exec_builtin(t_cmd *cmd, t_env *env);
int		is_builtin(char *command, t_cmd *cmd);
int		ft_export(t_cmd *cmd, t_env **env);
int		ft_unset(t_env **env, t_cmd *cmd);
t_env	*create_env_node(char *key, char *value);
void	add_or_update(t_env **env, char *key, char *value);
int		ft_cd(t_cmd *cmd, t_env **env);
int		check_flag(char *str);
int		ft_echo(t_cmd *cmd);
void	direct_and_close(int *fd);
void	handle_utils(t_redir *tmp, int *fd);
int		handle_redirections(t_cmd *cmd);
int		heredoc_utils(t_redir *tmp);
int		setup_tty(int *saved_stdin);
void	export_with_value(char *arg, t_env **env, char *equal);
void	fill_heredoc(char *stop, int *fd);
void	free_cmd_list(t_cmd **cmd);
void	free_token_list(t_token **token);
void	handle_sigint(int sig);
void	init_signals(void);
int		count_env_vars(t_env *env);
int		is_valid_identifier(char *key);
int		export_error(char *arg);
t_env	*look_for(t_env *env, char *key);
extern int	g_sig_status;
extern int	g_exit_status;
#endif
