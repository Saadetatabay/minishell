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