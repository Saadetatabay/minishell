/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:05 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:25:05 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command, t_cmd *cmd)
{
	if (ft_strncmp("pwd", command, 3) == 0 && command[3] == '\0')
		return (1);
	else if (ft_strncmp("exit", command, 4) == 0 && command[4] == '\0')
		return (1);
	else if (ft_strncmp("env", command, 3) == 0 && command[3] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& cmd->args[0][6] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& cmd->args[0][5] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& cmd->args[0][4] == '\0')
		return (1);
	else
		return (0);
}

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strncmp("pwd", cmd->args[0], 3) == 0 && cmd->args[0][3] == '\0')
		g_exit_status = ft_pwd();
	else if (ft_strncmp("exit", cmd->args[0], 4) == 0
		&& cmd->args[0][4] == '\0')
		ft_exit(cmd);
	else if (ft_strncmp("env", cmd->args[0], 3) == 0 && cmd->args[0][3] == '\0')
		g_exit_status = ft_env(env);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& cmd->args[0][6] == '\0')
		g_exit_status = ft_export(cmd, &env);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& cmd->args[0][5] == '\0')
		g_exit_status = ft_unset(&env, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0')
		g_exit_status = ft_cd(cmd, &env);
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& cmd->args[0][4] == '\0')
		g_exit_status = ft_echo(cmd);
}

t_env	*look_for(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	node->next = NULL;
	return (node);
}

void	add_or_update(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*temp;

	node = look_for(*env, key);
	if (node != NULL)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
		return ;
	}
	node = create_env_node(key, value);
	if (!node)
		return ;
	if (!*env)
		*env = node;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}
