/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:33:29 by satabay           #+#    #+#             */
/*   Updated: 2026/02/14 12:34:20 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **token)
{
	t_token	*tmp;
	t_token	*current;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		tmp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	*token = NULL;
}
