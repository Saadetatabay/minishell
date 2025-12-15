#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <ctype.h>

//Token türlerini
typedef enum e_token_type
{
    WORD,       // Komutlar, argümanlar (echo, ls, -l, dosya.txt)
    PIPE,       // |
    REDIRECT_IN, // <
    REDIRECT_OUT, // >
    APPEND,     // >>
    HEREDOC     // <<
} t_token_type;

typedef struct s_token
{
	char			*value; // token içeriği echo mesela
	t_token_type	type;//token türü (WORD)
	struct s_token	*next; //sonraki token
    struct s_token  *prev;
}	t_token;

typedef struct s_env
{
	char			*key;   // Örn: "USER"
	char			*value; // Örn: "satabay"
	struct s_env	*next;
}	t_env;

// Yönlendirme türleri (Input, Output, Append, Heredoc)
typedef enum e_redir_type
{
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // <<
}   t_redir_type;

// Yönlendirme Listesi (Her komutun kendi dosya yönlendirmeleri olabilir)
typedef struct s_redir
{
    t_redir_type    type;       // Türü ne? (<, >, >>)
    char            *file;      // Dosya adı ne? (örn: "outfile.txt")
    struct s_redir  *next;      // Başka yönlendirme var mı?
}   t_redir;

// ANA KOMUT YAPISI (Partnerinin Beklediği Şey)
typedef struct s_cmd
{
    char            **args;     // Komut ve argümanları (execve için hazır dizi!)
                                // Örn: args[0]="ls", args[1]="-la", args[2]=NULL
    
    t_redir         *redirections; // Giriş/Çıkış dosyaları listesi
    
    struct s_cmd    *next;      // Sırada başka komut var mı? (Pipe varsa dolu olur)
}   t_cmd;

t_token	*lexer(char	*input);
int	    handle_operator(t_token	**token_list, char *input, int i);
int	    handle_word(t_token **token_list, char *input, int i);
t_token	*lexer(char	*input);
t_token	*ft_new_token(char *content, t_token_type type);
void	token_add_list(t_token **token_list, t_token *new_token);
void    free_token_list(t_token **token);
void    print_tokens(t_token *token);
void	init_env(t_env **env_list, char **envp);
void    print_env(t_env *env);
char	*get_env_value(char *name, t_env *env_list);
char    *remove_quotes(char *str);
void	expander(t_token **token_list, t_env *env_list);
char	*var_name(char *s);
char	*replace_string(char *old_str, int start, int len_name, char *new);
void	expand_token(t_token *token, t_env *env_list);
t_cmd   *new_cmd_node(void);
t_cmd   *new_cmd_node(void);
char	**join_str_array(char *arr[], char *new_str);
t_redir	*add_redirect(t_token *token, t_cmd *cmd);

extern int  exit_status;

#endif