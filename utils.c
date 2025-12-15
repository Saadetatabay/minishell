#include "minishell.h"

void    print_env(t_env *env)
{
    while (env)
    {
        printf("Key: %s | Value: %s\n", env->key, env->value);
        env = env->next;
    }
}

#include "minishell.h"

void print_cmd_list(t_cmd *head)
{
    t_cmd   *current_cmd;
    t_redir *current_redir;
    int     i;

    current_cmd = head;
    int cmd_count = 0;
    
    printf("\n--- PARSER CIKTISI ---\n");
    
    // Ana Komut Listesinde Gezin (Pipe'lar)
    while (current_cmd)
    {
        printf("\n✅ KOMUT %d\n", ++cmd_count);

        // 1. Argümanları Yazdır
        printf("   -> Args: [");
        i = 0;
        if (current_cmd->args)
        {
            while (current_cmd->args[i])
            {
                printf("'%s'", current_cmd->args[i]);
                if (current_cmd->args[i + 1])
                    printf(", ");
                i++;
            }
        }
        printf("]\n");

        // 2. Yönlendirmeleri Yazdır
        current_redir = current_cmd->redirections;
        printf("   -> Redir: ");
        if (!current_redir)
            printf("Yok\n");
        else
        {
            while (current_redir)
            {
                printf(" %s:'%s'", 
                    current_redir->type == REDIR_IN ? "<" :
                    current_redir->type == REDIR_OUT ? ">" :
                    current_redir->type == REDIR_APPEND ? ">>" : "<<",
                    current_redir->file);
                current_redir = current_redir->next;
            }
            printf("\n");
        }
        
        current_cmd = current_cmd->next;
    }
    printf("----------------------\n");
}

char    *remove_quotes(char *str)
{
    char    *new;
    int     i;
    int     j;
    int     single_quote;
    int     double_quote;

    if (!str)
        return (NULL);
    single_quote = 0;
    double_quote = 0;
    i = 0;
    j = 0;
    new = malloc(sizeof(char)*(ft_strlen(str) + 1));
    while (str[i])
    {
        if (str[i] == '\'' && !double_quote)
                single_quote = !single_quote;
        else if (str[i] == '"' && !single_quote)
                    double_quote = !double_quote;
        else
        {
            new[j] = str[i];
            j++;
        }
        i++;
    }
    new[j] = '\0';
    return (new);
}