#include "minishell.h"

t_env   *look_for(t_env *env, char *key)
{
    t_env *temp;

    temp = env;
    while(temp != NULL)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	add_or_update(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*temp;

	node = look_for(*env, key);
	if (node != NULL)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
		return;
	}
	node = create_env_node(key, value);
    if (!node)
        return;
    if (!*env)
	    *env = node;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

int ft_export(t_cmd *cmd, t_env **env)
{
    int     i;
    char    *key;
    char    *value;
    char    *equal;

    i = 1;
    while(cmd->args[i] != NULL)
    {
        equal = ft_strchr(cmd->args[i], '=');
        if(equal != NULL)
        {
            key = ft_substr(cmd->args[i], 0, equal - cmd->args[i]);
            value = ft_strdup(equal + 1);
        }
        else
        {
            key = ft_strdup(cmd->args[i]);
            value = NULL;
        }
        add_or_update(env, key, value);
        free(value);
        free(key);
        i++;
    }
    return (0);
}