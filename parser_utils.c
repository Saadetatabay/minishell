#include "minishell.h"

t_cmd   *new_cmd_node(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    //içindeki değerlerii NULL yapı-ıyrouz çünkü kontrol ettiğimizde çöp değer olmamalı
    cmd->args = NULL;
    cmd->redirections = NULL;
    cmd->next = NULL;
    return (cmd);
}

char	**join_str_array(char *arr[], char *new_str)
{
    int		size;
	int		j;
    char    **new_array;

    size = 0;
    if(arr)
    {
        while (arr[size])
            size++;
    }
	new_array = malloc(sizeof(char *)*(size + 2));
	if (!new_array)
		return NULL;
	j = 0;
	while (j < size)
	{
		new_array[j] = ft_strdup(arr[j]);
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

	if (!token->next || token->next->type != WORD)
		return NULL; //BURADA HATA GELECEK SONRA
	redir_new = malloc(sizeof(t_redir));
	if (!redir_new)
		return NULL; // MALLOC HATASI
	redir_new->file = ft_strdup(token->next->value);
	redir_new->next = NULL;
	if (token->type == REDIRECT_IN)
		redir_new->type = REDIR_IN;
	else if (token->type == REDIRECT_OUT)
		redir_new->type = REDIR_OUT;
	else if (token->type == APPEND)
		redir_new->type = REDIR_APPEND;
	else if (token->type == HEREDOC)
		redir_new->type = REDIR_HEREDOC;
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
