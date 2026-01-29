/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:03:37 by satabay           #+#    #+#             */
/*   Updated: 2026/01/30 00:32:49 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char	*input)
{
	int		i;
	int		len;
	t_token	*token_list;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += handle_operator(&token_list, input, i);
		else
		{
			len = handle_word(&token_list, input, i);
			if (len == -1)
				return (NULL);
			i += len;
		}
	}
	return (token_list);
}

int	handle_operator(t_token	**token_list, char *input, int i)
{
	int				ret;
	t_token			*new_token;
	t_token_type	type;

	ret = 2;
	if (input[i + 1] && input[i] == '<' && input[i + 1] == '<')
		type = HEREDOC;
	else if (input[i + 1] && input[i] == '>' && input[i + 1] == '>')
		type = APPEND;
	else
	{
		ret = 1;
		if (input[i] == '<')
			type = REDIRECT_IN;
		else if (input[i] == '>')
			type = REDIRECT_OUT;
		else
			type = PIPE;
	}
	new_token = ft_new_token(ft_substr(input, i, ret), type);
	token_add_list(token_list, new_token);
	return (ret);
}

int	handle_word(t_token **token_list, char *input, int i)
{
	int		start;
	char	*content;

	start = i;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = skip_quotes(input, i);
			if (i == -1)
			{
				printf("Minishell: unclosed quote error\n");
				return (-1);
			}
		}
		i++;
	}
	content = ft_substr(input, start, i - start);
	token_add_list(token_list, ft_new_token(content, WORD));
	return (i - start);
}

t_token	*ft_new_token(char *content, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	token_add_list(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (!*token_list)
	{
		*token_list = new_token;
	}
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}
