/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:54 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:25:54 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_env **env, char *delete)
{
	t_env	*prev;
	t_env	*current;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, delete, ft_strlen(delete) + 1) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value != NULL)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_env **env, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		delete_node(env, cmd->args[i]);
		i++;
	}
	return (0);
}
