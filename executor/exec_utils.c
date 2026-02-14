/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:06 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:26:06 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*key_value(t_env *env)
{
	char	*temp;
	char	*key_and_value;

	temp = ft_strjoin(env->key, "=");
	if (!temp)
		return (NULL);
	key_and_value = ft_strjoin(temp, env->value);
	free(temp);
	return (key_and_value);
}

char	**env_to_array(t_env *env)
{
	t_env		*temp;
	int			count;
	char		**arr;
	int			i;

	i = 0;
	temp = env;
	count = count_env_vars(temp);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	while (temp != NULL)
	{
		arr[i] = key_value(temp);
		i++;
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	setup_child_fds(t_cmd *cmd, int prev_fd, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	**arr;
	char	*path;
	char buffer[1024];
	ssize_t n;

	if (!cmd->args || !cmd->args[0])
    {
        while ((n = read(0, buffer, sizeof(buffer))) > 0)
            write(1, buffer, n);
        exit(0);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0], cmd))
	{
		exec_builtin(cmd, env);
		exit(0);
	}
	arr = env_to_array(env);
	path = find_path(cmd->args[0], env);
	if (!path)
	{
		write(2, "Command not found\n", 18);
		exit(127);
	}
	execve(path, cmd->args, arr);
	perror("execve");
	exit(1);
}
