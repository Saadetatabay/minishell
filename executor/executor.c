/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:09 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:26:09 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_fds(cmd, prev_fd, fd);
	if (handle_redirections(cmd) == 1)
		exit(1);
	execute_command(cmd, env);
}

static void	exec_parent_builtin(t_cmd *cmd, t_env *env)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(cmd) == 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return ;
	}
	exec_builtin(cmd, env);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

static void	wait_children(pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	while (wait(NULL) != -1)
	{
	}
}

static int	is_parent_builtin(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0] || cmd->next)
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	return (0);
}

void	executor(t_cmd *cmd, t_env *env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	if (is_parent_builtin(cmd))
		return (exec_parent_builtin(cmd, env));
	prev_fd = -1;
	while (cmd != NULL)
	{
		if (cmd->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
			handle_child_process(cmd, env, prev_fd, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			prev_fd = fd[0];
		if (cmd->next)
			close(fd[1]);
		cmd = cmd->next;
	}
	wait_children(pid);
}
