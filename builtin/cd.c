#include "minishell.h"

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
	if (cmd->args[1] == NULL)
	{
		path = get_env_value("HOME", *env);
		if (path == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", *env);
		if (path == NULL)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return (1);
		}
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	else
		path = cmd->args[1];
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
