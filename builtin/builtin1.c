#include "minishell.h"

int ft_pwd(void)
{
    char loc[1024];
    if(getcwd(loc, sizeof(loc)) != NULL)
    {
        ft_putstr_fd(loc, 1);
        write(1,"\n",1);
        return (0);
    }
    write(1,"pwd error\n",10);
    return (1);
}

int ft_env(t_env *env)
{
    t_env *temp;
    char *t;
    temp = env;
    while(temp != NULL)
    {
        if(temp->value != NULL)
        {
            t = key_value(temp);
            ft_putstr_fd(t, 1);
            write(1,"\n",1);
            free(t);
        }
        temp = temp->next;
    }
    return (0);
}

int ft_exit(void)
{
    write(1,"exit\n",5);
    exit(0);
    return (0);
}