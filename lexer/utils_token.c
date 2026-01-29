/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:02:35 by satabay           #+#    #+#             */
/*   Updated: 2026/01/30 00:16:58 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	skip_quotes(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (-1);
	return (i);
}
