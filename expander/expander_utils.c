/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:16:10 by satabay           #+#    #+#             */
/*   Updated: 2026/01/29 22:28:03 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c, int *sq, int *dq)
{
	if (c == '\'' && !*dq)
	{
		*sq = !*sq;
		return (1);
	}
	else if (c == '"' && !*sq)
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;

	if (!str)
		return (NULL);
	single_quote = 0;
	double_quote = 0;
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (!is_quote(str[i], &single_quote, &double_quote))
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
