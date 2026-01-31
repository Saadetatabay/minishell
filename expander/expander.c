/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:59:43 by satabay           #+#    #+#             */
/*   Updated: 2026/01/31 13:38:05 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token **token_list, t_env *env_list)
{
	t_token	*token;
	char	*cleaned_str;

	token = *token_list;
	while (token)
	{
		if (token->type == WORD && (!token->prev
				|| token->prev->type != HEREDOC))
		{
			if (ft_strchr(token->value, '$'))
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
			expand_process(token, &i, env_list);
		i++;
	}
}

char	*var_name(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(s[0]))
		return (ft_substr(s, 0, 1));
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (ft_substr(s, 0, i));
}

char	*replace_string(char *old_str, int start, int len_name, char *new)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;
	int		suffix_len;

	prefix = ft_substr(old_str, 0, start);
	suffix_len = ft_strlen(old_str) - (start + 1 + len_name);
	suffix = ft_substr(old_str, start + 1 + len_name, suffix_len);
	temp = ft_strjoin(prefix, new);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	return (result);
}

void	expand_process(t_token *token, int *i, t_env *env_list)
{
	char	*name;
	char	*value;
	char	*new_str;

	name = var_name(&token->value[*i + 1]);
	if (!name || ft_strlen(name) == 0)
	{
		if (name)
			free(name);
		(*i)++;
		return ;
	}
	value = get_expansion_value(name, env_list);
	new_str = replace_string(token->value, *i, ft_strlen(name), value);
	free(token->value);
	token->value = new_str;
	*i = *i + ft_strlen(value) - 1;
	free(value);
	free(name);
}
