/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:16:31 by satabay           #+#    #+#             */
/*   Updated: 2026/01/31 12:48:04 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	**join_str_array(char *arr[], char *new_str)
{
	int		size;
	int		j;
	char	**new_array;

	size = 0;
	while (arr && arr[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	j = 0;
	while (j < size)
	{
		new_array[j] = ft_strdup(arr[j]);
		if (arr)
			free(arr[j]);
		j++;
	}
	new_array[j] = ft_strdup(new_str);
	new_array[j + 1] = NULL;
	if (arr)
		free(arr);
	return (new_array);
}

t_redir	*add_redirect(t_token *token, t_cmd *cmd)
{
	t_redir	*redir_new;
	t_redir	*temp;

	if (!token->next)
		return (syntax_error("newline"));
	if (token->next->type != WORD)
		return (syntax_error(token->next->value));
	redir_new = malloc(sizeof(t_redir));
	if (!redir_new)
		return (NULL);
	redir_new->file = ft_strdup(token->next->value);
	redir_new->next = NULL;
	redir_new->type = redir_type_atama(token->type);
	if (!cmd->redirections)
		cmd->redirections = redir_new;
	else
	{
		temp = cmd->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = redir_new;
	}
	return (redir_new);
}

void	*syntax_error(char *s)
{
	printf("Minishell: syntax error near unexpected token '%s'\n", s);
	return (NULL);
}

int	redir_type_atama(int token_type)
{
	if (token_type == REDIRECT_IN)
		return (REDIR_IN);
	else if (token_type == REDIRECT_OUT)
		return (REDIR_OUT);
	else if (token_type == APPEND)
		return (REDIR_APPEND);
	else if (token_type == HEREDOC)
		return (REDIR_HEREDOC);
	return (0);
}
