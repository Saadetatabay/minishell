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
		&&cmd->args[0][6] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&&cmd->args[0][5] == '\0')
		return (1);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& cmd->args[0][2] == '\0')
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
	else if (ft_strncmp("env", cmd->args[0], 3) == 0
		&& cmd->args[0][3] == '\0')
		g_exit_status = ft_env(env);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& cmd->args[0][6] == '\0')
		g_exit_status = ft_export(cmd, &env);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& cmd->args[0][5] == '\0')
		g_exit_status = ft_unset(&env, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& cmd->args[0][2] == '\0')
		g_exit_status = ft_cd(cmd, &env);
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& cmd->args[0][4] == '\0')
		g_exit_status = ft_echo(cmd);
}
