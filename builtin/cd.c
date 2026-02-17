/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:43 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:25:43 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (cmd->args[1] == NULL)
	{
		path = get_env_value("HOME", env);
		if (path == NULL)
			write(2, "minishell: cd: HOME not set\n", 28);
		return (path);
	}
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", env);
		if (path == NULL)
			write(2, "minishell: cd: OLDPWD not set\n", 30);
		else
		{
			ft_putstr_fd(path, 1);
			write(1, "\n", 1);
		}
		return (path);
	}
	return (cmd->args[1]);
}

int	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (getcwd(old_pwd, 1024) == NULL)
	{
		write(2, "minishell: cd: getcwd error\n", 28);
		return (1);
	}
	path = get_cd_path(cmd, *env);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: No such file or directory\n", 42);
		return (1);
	}
	add_or_update(env, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, 1024))
		add_or_update(env, "PWD", new_pwd);
	return (0);
}
