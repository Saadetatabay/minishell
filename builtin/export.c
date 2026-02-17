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

static int  is_valid_identifier(char *key)
{
	int	i;

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

static void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value && env->value[0])
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

static int	export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

static void export_arg(char *arg, t_env **env)
{
  char	*key;
  char	*value;
  char	*equal;

  equal = ft_strchr(arg, '=');
  if (equal != NULL)
  {
	  key = ft_substr(arg, 0, equal - arg);
	  value = ft_strdup(equal + 1);
	  if (!is_valid_identifier(key))
	  {
		  export_error(arg);
		  free(key);
		  free(value);
		  return;
	  }
	  add_or_update(env, key, value);
	  free(value);
	  free(key);
  }
  else 
  {
	  key = ft_strdup(arg);
	  if (!is_valid_identifier(key))
	  {
		  export_error(arg);
		  free(key);
		  return;
	  }
	  if (!look_for(*env, key))
		  add_or_update(env, key, "");
	  free(key);
  }
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	i;

	if (cmd->args[1] == NULL)
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	while (cmd->args[i] != NULL)
	{
		export_arg(cmd->args[i], env);
		i++;
	}
	return (0);
}
