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

char *find_path(char *cmd, t_env *env)
{
    char *path;
    char *temp;
    char *new;
    char **arr;
    int i;

    i = 0;
    if(ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    path = path_value(env);
    //birisi gelip pathi silerse diye
    if(!path)
        return (NULL);
    arr = ft_split(path, ':');
    while(arr[i] != NULL)
    {
        temp = ft_strjoin(arr[i], "/");
        new = ft_strjoin(temp, cmd);
        free(temp);
        if(access(new, X_OK) == 0)
        {
            free_arr(arr);
            return (new);
        }
        free(new);
        i++;
    }
    free_arr(arr);
    return(NULL);
}