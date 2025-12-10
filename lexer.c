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