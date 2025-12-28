#include "minishell.h"

int ft_cd(t_cmd *cmd, t_env **env)
{
    char *path;
    char buffer[1024];

    if (cmd->args[1] == NULL)
    {
        path = get_env_value("HOME", *env);  
        if (path == NULL)
        {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (1);
        }
    }
    else
        path = cmd->args[1];
    if (chdir(path) == -1)
    {
        write(2, "minishell: cd: No such file or directory\n", 42);
        return (1);
    }
    if (getcwd(buffer, 1024))
        add_or_update(env, "PWD", buffer);
     return (0);
}