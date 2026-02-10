#include "minishell.h"

static void	handle_child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fd)
{
	char	**arr;
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1 && (dup2(prev_fd, 0), close(prev_fd), 0))
		;
	if (cmd->next && (close(fd[0]), dup2(fd[1], 1), close(fd[1]), 0))
		;
	if (handle_redirections(cmd) == 1)
		exit(1);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0], cmd))
		(exec_builtin(cmd, env), exit(0));
	if (!cmd->args || !cmd->args[0])
		exit(0);
	arr = env_to_array(env);
	path = find_path(cmd->args[0], env);
	if (!path)
		(write(2, "Command not found\n", 18), exit(127));
	execve(path, cmd->args, arr);
	(perror("execve"), exit(1));
}

static int	exec_parent_builtin(t_cmd *cmd, t_env *env)
{
	int	saved_stdout;
	int	saved_stdin;

	if (!cmd->args || !cmd->args[0] || cmd->next)
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 3) != 0
		&& ft_strncmp(cmd->args[0], "exit", 5) != 0
		&& ft_strncmp(cmd->args[0], "export", 7) != 0
		&& ft_strncmp(cmd->args[0], "unset", 6) != 0)
		return (0);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(cmd) == 1)
		return (dup2(saved_stdout, 1), dup2(saved_stdin, 0),
			close(saved_stdout), close(saved_stdin), 1);
	exec_builtin(cmd, env);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	(close(saved_stdout), close(saved_stdin));
	return (1);
}

static void	execute_pipeline(t_cmd *cmd, t_env *env, int *prev_fd, pid_t *pid)
{
	int	fd[2];

	while (cmd != NULL)
	{
		if (cmd->next)
			pipe(fd);
		*pid = fork();
		if (*pid == 0)
			handle_child_process(cmd, env, *prev_fd, fd);
		else
		{
			if (*prev_fd != -1)
				close(*prev_fd);
			if (cmd->next && (*prev_fd = fd[0], close(fd[1]), 0))
				;
		}
		cmd = cmd->next;
	}
}

static void	wait_children(pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	while (wait(NULL) != -1)
		;
}

void	executor(t_cmd *cmd, t_env *env)
{
	int		prev_fd;
	pid_t	pid;

	if (exec_parent_builtin(cmd, env))
		return ;
	prev_fd = -1;
	execute_pipeline(cmd, env, &prev_fd, &pid);
	wait_children(pid);
}