#include "minishell.h"

t_cmd   *new_cmd_node(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    //içindeki değerlerii NULL yapı-ıyrouz çünkü kontrol ettiğimizde çöp değer olmamalı
    cmd->args = NULL;
    cmd->redirections = NULL;
    cmd->next = NULL;
    return (cmd);
}