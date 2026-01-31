/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:49:03 by satabay           #+#    #+#             */
/*   Updated: 2026/01/31 13:41:56 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_token(t_token *token_list)
{
	t_token	*current_token;
	t_cmd	*head;
	t_cmd	*current;

	if (!token_list)
		return (NULL);
	if (token_list->type == PIPE)
		return (syntax_error("|"));
	current_token = token_list;
	head = new_cmd_node();
	if (!head)
		return (NULL);
	current = head;
	while (current_token)
	{
		if (!process_token(&current_token, &current, &head))
			return (NULL);
		current_token = current_token->next;
	}
	return (head);
}

int	process_token(t_token **token, t_cmd **current, t_cmd **head)
{
	if ((*token)->type == PIPE)
		return (handle_pipe(*token, head, current));
	else if ((*token)->type == WORD)
		return (word_handle(*token, *current, head));
	else
		return (redirection_handle(token, *current, head));
}

int	handle_pipe(t_token *token, t_cmd **head, t_cmd **current)
{
	t_cmd	*new_cmd;

	if (!token->next || token->next->type == PIPE)
	{
		free_cmd_list(head);
		syntax_error("|");
		return (0);
	}
	new_cmd = new_cmd_node();
	if (!new_cmd)
	{
		free_cmd_list(head);
		return (0);
	}
	(*current)->next = new_cmd;
	*current = new_cmd;
	return (1);
}

int	word_handle(t_token *token, t_cmd *current, t_cmd **head)
{
	current->args = join_str_array(current->args, token->value);
	if (!current->args)
	{
		free_cmd_list(head);
		return (0);
	}
	return (1);
}

int	redirection_handle(t_token **token, t_cmd *current, t_cmd **head)
{
	if (!add_redirect(*token, current))
	{
		free_cmd_list(head);
		return (0);
	}
	*token = (*token)->next;
	return (1);
}
