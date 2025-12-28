#include "minishell.h"

void execute_cmd(t_cmd *cmd, t_env *env)
{
    pid_t pid;
    char **arr;
    char *path;

    if(cmd->args && cmd->args[0] && is_builtin(cmd->args[0], cmd) == 1)
    {
        exec_builtin(cmd, env);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        if (handle_redirections(cmd) == 1)
            exit(1);
        if (!cmd->args || !cmd->args[0])
            exit(0);
        arr = env_to_array(env);
        path = find_path(cmd->args[0], env);
        if(path == NULL)
        {
            write(2,"command not found\n",19);
            exit(127);
        }
        execve(path, cmd->args, arr);
        perror("execve");
        exit(1);
    }
    else if(pid > 0)
        waitpid(pid, NULL, 0);
    else
    {
        perror("fork");
        return;
    }
}