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

void	init_env(t_env **env_list, char **envp)
{
	int		i;
	t_env	*new;
	char	*find;
	char	*value;
	char	*key;

	i = 0;
	while (envp[i])
	{
		find = ft_strchr(envp[i],'=');
		if (find)
		{
			key = ft_substr(envp[i], 0, find - envp[i]);
			value = ft_strdup(find + 1);
			new = new_env_node(key, value);
			env_add_back(env_list, new);
		}
		i++;
	}
}