/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:25:11 by satabay           #+#    #+#             */
/*   Updated: 2026/02/17 20:25:11 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_tty(int *saved_stdin)
{
	int	tty_fd;

	*saved_stdin = dup(STDIN_FILENO);
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	return (0);
}

void	export_with_value(char *arg, t_env **env, char *equal)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!is_valid_identifier(key))
	{
		export_error(arg);
		free(key);
		free(value);
		return ;
	}
	add_or_update(env, key, value);
	free(value);
	free(key);
}
