#include "minishell.h"

void    print_env(t_env *env)
{
    while (env)
    {
        printf("Key: %s | Value: %s\n", env->key, env->value);
        env = env->next;
    }
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
    return (new);
}