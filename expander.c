#include "minishell.h"

void	expander(t_token **token_list, t_env *env_list)
{
	t_token	*token;
	char	*cleaned_str;
	token = *token_list;
	while (token)
	{
		if (token->type == WORD)
		{
			if (ft_strchr(token->value,'$'))
				expand_token(token, env_list);
			cleaned_str = remove_quotes(token->value);
			free(token->value);
			token->value = cleaned_str;
		}
		token = token->next;
	}
}

void	expand_token(t_token *token, t_env *env_list)
{
	int	i;
	int	single_quote;
	int	double_quote;
	char	*name;
	char	*value;
	char	*new_deger;
	char	*temp_value;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (token->value[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		else if (token->value[i] == '$' && single_quote == 0)
		{
			name = var_name(&token->value[i + 1]); //$USER mesela burada USER ı alıyoruz
			if (!name) // eğer isim yoksa sadece $işareti atla
			{
				i++;
				continue;
			}
			if (strncmp(name, "?",2) == 0)
			{
				value = ft_itoa(exit_status);
			}
			else
			{
				temp_value = get_env_value(name, env_list); // USER ın env listesinde karşılığına bakar satabay mesela
				if (temp_value)
					value = ft_strdup(value);
				else
					value = ft_strdup("");
			}
				new_deger = replace_string(token->value, i,ft_strlen(name), value);
				free(token->value);
				token->value = new_deger;
				i = i + ft_strlen(value) - 1; //satabay
				free(value);
				free(name);
		}
		i++;
	}
}

char	*var_name(char *s)
{
	int i;

	i = 0;
	if (s[0] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(s[0]))
		return (ft_substr(s, 0, 1));
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (ft_substr(s, 0,i));
}

char	*replace_string(char *old_str, int start, int len_name, char *new)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;

	prefix = ft_substr(old_str, 0, start); // $ işaretine kadar olan kısmı aldık
	suffix = ft_substr(old_str, start + 1 + len_name, ft_strlen(old_str)); // $USER kısmını geçip devamında olan kısmı aldık
	temp = ft_strjoin(prefix, new);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	return (result);
}