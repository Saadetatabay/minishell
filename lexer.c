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
			//kelime kısmı
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
	new_token = newtoken(content, type);
	token_add_list(token_list, new_token);
	return (ret);
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