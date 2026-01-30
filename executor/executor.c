#include "minishell.h"

// void execute_cmd(t_cmd *cmd, t_env *env)
// {
//     pid_t pid;
//     char **arr;
//     char *path;

//     if(cmd->args && cmd->args[0] && is_builtin(cmd->args[0], cmd) == 1)
//     {
//         exec_builtin(cmd, env);
//         return;
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         if (handle_redirections(cmd) == 1)
//             exit(1);
//         if (!cmd->args || !cmd->args[0])
//             exit(0);
//         arr = env_to_array(env);
//         path = find_path(cmd->args[0], env);
//         if(path == NULL)
//         {
//             write(2,"command not found\n",19);
//             exit(127);
//         }
//         execve(path, cmd->args, arr);
//         perror("execve");
//         exit(1);
//     }
//     else if(pid > 0)
//         waitpid(pid, NULL, 0);
//     else
//     {
//         perror("fork");
//         return;
//     }
// }

void	executor(t_cmd *cmd, t_env *env)
{
	char **arr;
    char *path;
	int		fd[2];
	int		previous_fd = -1; //önceki borunun ucuc başta yok diye -1
	pid_t	pid;
	int		status;

	if(cmd->args && cmd->args[0] && is_builtin(cmd->args[0], cmd) == 1)
    {
        exec_builtin(cmd, env);
        return;
    }
	while (cmd != NULL)
	{
		if (cmd->next)
			pipe(fd); //fd[0] okuma fd[1] yazma ucu
		pid = fork();
		if (pid == 0) //childprocess
		{
			if (previous_fd != -1)
			{
				dup2(previous_fd,0);
				close(previous_fd);
			}
			if (cmd->next)
			{
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
			}
			// ÖNCE YÖNLENDİRMELER (Dosya boruyu ezer)
			if (handle_redirections(cmd) == 1)
				exit(1);

			// Built-in mi? (Eğer pipe içindeyse built-in burada çalışmalı)
			if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0], cmd))
			{
				exec_builtin(cmd, env);
				exit(0); // Çocuğu öldür ki döngüye devam etmesin
			}

			// Sistem Komutu Hazırlığı
			if (!cmd->args || !cmd->args[0])
				exit(0);

			arr = env_to_array(env);
			path = find_path(cmd->args[0], env);

			if (!path)
			{
				write(2, "Command not found\n", 18);
				exit(127);
			}

			execve(path, cmd->args, arr);
			perror("execve"); // Sadece hata olursa buraya gelir
			exit(1);
		}
		else
		{
			if (previous_fd != -1)
				close(previous_fd);
			if (cmd->next)
			{
				previous_fd = fd[0];
				close(fd[1]);
			}
		}
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status); // Ctrl+C gibi sinyaller için
	while(wait(NULL) != -1);
}