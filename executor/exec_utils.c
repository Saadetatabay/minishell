#include "minishell.h"

int count_env_vars(t_env *env)
{
    int count;
    count = 0;
    while(env != NULL)
    {
        count++;
        env = env->next;
    }
    return (count);
}
//key ve valuelar birlestirildi USER=satabay gibi
char*   key_value(t_env *env)
{
    char *temp;
    char *key_and_value;
    temp = ft_strjoin(env->key, "=");
    if(!temp)
        return(NULL);
    key_and_value = ft_strjoin(temp, env->value);
    free(temp);
    return (key_and_value);
}
//execve() ye gondermek icin USER=satabay, USER=ayonal lari arraya ceviriyoruz
char** env_to_array(t_env *env)
{
    t_env *temp;
    int count;
    char **arr;
    int i;

    i = 0;
    temp = env;
    count = count_env_vars(temp);
    arr = (char **)malloc(sizeof(char *) * (count + 1));
    if(!arr)
        return (NULL);
    while(temp != NULL)
    {
        arr[i] = key_value(temp);
        i++;
        temp = temp->next;
    }
    arr[i] = NULL;
    return (arr);
}