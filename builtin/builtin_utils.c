#include "minishell.h"

int is_builtin(char *command, t_cmd *cmd)
{
    if(ft_strncmp("pwd", command, 4) == 0)
        return (1);
    else if(ft_strncmp("exit", command, 5) == 0)
        return (1);
    else if(ft_strncmp("env", command, 4) == 0)
        return (1);
    else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
        return (1);
    else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
        return (1);
    else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        return (1);
    else
        return (0);
}
void exec_builtin(t_cmd *cmd, t_env *env)
{
    if(ft_strncmp("pwd",cmd->args[0], 4) == 0)
        ft_pwd();
    else if(ft_strncmp("exit", cmd->args[0], 5) == 0)
        ft_exit(cmd);
    else if(ft_strncmp("env", cmd->args[0], 4) == 0)
        ft_env(env);
    else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
        ft_export(cmd, &env);
    else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
        ft_unset(&env, cmd);
    else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        ft_cd(cmd, &env);
    else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        ft_echo(cmd);
}