/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:37 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:25:37 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_pwd(void)
{
	char	loc[1024];

	if (getcwd(loc, sizeof(loc)) != NULL)
	{
		ft_putstr_fd(loc, 1);
		write(1, "\n", 1);
		return (0);
	}
	write(1, "pwd error\n", 10);
	return (1);
}

int	ft_env(t_env *env)
{
	t_env	*temp;
	char	*t;

	temp = env;
	while (temp != NULL)
	{
		if (temp->value != NULL && temp->value[0] != '\0')
		{
			t = key_value(temp);
			ft_putstr_fd(t, 1);
			write(1, "\n", 1);
			free(t);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	write (1, "exit\n", 5);
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd->args[1], ft_strlen(cmd->args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		exit_code = ft_atoi(cmd->args[1]);
		exit(exit_code % 256);
	}
	exit(0);
	return (0);
}
