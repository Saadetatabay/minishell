#include "minishell.h"

t_env   *new_env_node(char *key, char *value)
{
	t_env	*new;

    new = malloc(sizeof(t_env));
	if (!new)
		return NULL;
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env_list, t_env *new)
{
	t_env	*temp;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
