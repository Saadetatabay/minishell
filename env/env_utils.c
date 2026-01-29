/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:58:04 by satabay           #+#    #+#             */
/*   Updated: 2026/01/29 21:58:06 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shell_level(t_env *env_list)
{
	t_env	*temp;
	int		lvl;

	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, "SHLVL", 6) == 0)
		{
			lvl = ft_atoi(temp->value);
			lvl++;
			free(temp->value);
			temp->value = ft_itoa(lvl);
			return ;
		}
		temp = temp->next;
	}
}

static void	create_default_env(t_env **env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env_add_back(env_list, new_env_node(ft_strdup("PWD"), cwd));
	env_add_back(env_list, new_env_node(ft_strdup("SHLVL"),
			ft_strdup("1")));
	env_add_back(env_list, new_env_node(ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
}
