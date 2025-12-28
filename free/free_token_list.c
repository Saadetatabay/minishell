#include "minishell.h"

void    free_token_list(t_token **token)
{
    t_token *tmp;
    t_token *current;

    if (!token || !*token)
        return;
    current = *token;
    while (current)
    {
        tmp = current->next;
        if (current->value)
            free(current->value); //string
        free(current);            //düğüm
        current = tmp;
    }
    *token = NULL;
}