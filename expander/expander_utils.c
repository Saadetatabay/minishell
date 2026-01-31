/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:16:10 by satabay           #+#    #+#             */
/*   Updated: 2026/01/31 13:37:59 by satabay          ###   ########.fr       */
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

char	*get_expansion_value(char *name, t_env *env_list)
{
	char	*temp_val;

	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(exit_status));
	temp_val = get_env_value(name, env_list);
	if (temp_val)
		return (ft_strdup(temp_val));
	return (ft_strdup(""));
}
