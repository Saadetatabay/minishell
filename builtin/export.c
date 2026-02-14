/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:50 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:25:50 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Key validation fonksiyonu
static int is_valid_identifier(char *key)
{
    int i;

    if (!key || !key[0])
        return (0);
    if (!ft_isalpha(key[0]) && key[0] != '_')
        return (0);
    i = 0;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

t_env *look_for(t_env *env, char *key)
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

t_env *create_env_node(char *key, char *value)
{
    t_env *node;

    node = (t_env *)malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = ft_strdup(key);
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = ft_strdup("");  // ← NULL yerine boş string
    node->next = NULL;
    return (node);
}

void add_or_update(t_env **env, char *key, char *value)
{
    t_env *node;
    t_env *temp;

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
    t_env   *temp;

    // Argümansız: tüm export'ları göster
    if (cmd->args[1] == NULL)
    {
        temp = *env;
        while (temp)
        {
            printf("declare -x %s", temp->key);
            if (temp->value && temp->value[0])  // ← Boş string kontrolü
                printf("=\"%s\"", temp->value);
            printf("\n");
            temp = temp->next;
        }
        return (0);
    }

    i = 1;
    while(cmd->args[i] != NULL)
    {
        equal = ft_strchr(cmd->args[i], '=');
        
        if (equal != NULL)  // export KEY=VALUE
        {
            key = ft_substr(cmd->args[i], 0, equal - cmd->args[i]);
            value = ft_strdup(equal + 1);
            
            if (!is_valid_identifier(key))
            {
                write(2, "minishell: export: `", 20);
                write(2, cmd->args[i], ft_strlen(cmd->args[i]));
                write(2, "': not a valid identifier\n", 26);
                free(key);
                free(value);
                i++;
                continue;
            }
            
            add_or_update(env, key, value);
            free(value);
            free(key);
        }
        else  // export KEY (değersiz)
        {
            key = ft_strdup(cmd->args[i]);
            
            if (!is_valid_identifier(key))
            {
                write(2, "minishell: export: `", 20);
                write(2, cmd->args[i], ft_strlen(cmd->args[i]));
                write(2, "': not a valid identifier\n", 26);
                free(key);
                i++;
                continue;
            }
            
            // Değişken zaten varsa dokunma, yoksa boş ekle
            if (!look_for(*env, key))
                add_or_update(env, key, "");
            
            free(key);
        }
        i++;
    }
    return (0);
}