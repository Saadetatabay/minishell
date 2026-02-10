#include "minishell.h"
//key de path var mı diye bakıyor varsa onun valuesini alıyor mesela usr/bin gibi
char *path_value(t_env *env)
{
    while (env != NULL)
    {
        if (ft_strncmp(env->key, "PATH", 5) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
void free_arr(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char	*check_access(char **arr, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (arr[i])
	{
		temp = ft_strjoin(arr[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**arr;
	char	*res;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = path_value(env);
	if (!path)
		return (NULL);
	arr = ft_split(path, ':');
	if (!arr)
		return (NULL);
	res = check_access(arr, cmd);
	free_arr(arr);
	return (res);
}