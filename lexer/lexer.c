#include "minishell.h"

t_token	*lexer(char	*input)
{
	int		i;
	t_token	*token_list;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i]==' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break;
		//operatörleri yakalmak için
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += handle_operator(&token_list, input, i);
		else
		{
			i += handle_word(&token_list, input, i);
		}
	}
	return (token_list);
}

int	handle_operator(t_token	**token_list, char *input, int i)
{
	int				ret;
	t_token			*new_token;
	t_token_type	type;
	char			*content;

	if (input[i + 1] && input[i]== '<' && input[i + 1] == '<')
	{
		content = ft_strdup("<<");
		type = HEREDOC;
		ret = 2;
	}
	else if (input[i + 1] && input[i]== '>' && input[i + 1] == '>')
	{
		content = ft_strdup(">>");
		type = APPEND;
		ret = 2;
	}
	else
	{
		ret = 1;
		if (input[i] == '<')
			type = REDIRECT_IN;
		else if (input[i] == '>')
			type = REDIRECT_OUT;
		else
			type = PIPE;
		content = ft_substr(input, i, 1);
	}
	new_token = ft_new_token(content, type);
	token_add_list(token_list, new_token);
	return (ret);
}

int	handle_word(t_token **token_list, char *input, int i)
{
	int		start;
	char	quato;
	char	*content;
	t_token	*new_token;

	start = i;
	while (input[i] && !isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>') //ft_isspace yaz
	{
		// "ls | wc" şeklinde kısmı aldım
		if (input[i] == '"' || input[i] == '\'')
		{
			quato = input[i];
			i++;
			while (input[i] && input[i] != quato)
				i++;
			if (input[i])
				i++;
		}
		else // tırnak içinde olmayan kelime
			i++;
	}
	content = ft_substr(input, start, i-start);
	new_token = ft_new_token(content,WORD);
	token_add_list(token_list, new_token);
	return (i-start);
}


t_token	*ft_new_token(char *content, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return NULL;
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