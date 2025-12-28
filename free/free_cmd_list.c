#include "minishell.h"

void    free_str_array(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    free_redirections(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->file)
            free(redir->file);
        free(redir);
        redir = tmp;
    }
}

void    free_cmd_list(t_cmd **cmd)
{
    t_cmd *tmp;
    t_cmd *current;

    if (!cmd || !*cmd)
        return;
    current = *cmd;
    while (current)
    {
        tmp = current->next;
        
        //argümanları free
        if (current->args)
            free_str_array(current->args);
            
        //redir frere
        if (current->redirections)
            free_redirections(current->redirections);
            
        free(current);
        current = tmp;
    }
    *cmd = NULL;
}
