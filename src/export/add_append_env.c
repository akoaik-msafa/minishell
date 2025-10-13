/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_append_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:14:32 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 12:50:02 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	append_to_env(char *arg, t_env *env, int index, t_list_head *env_head)
{
	char	*new_value;
	char	*result;
	int		existing_len;
	int		new_len;

	new_value = ft_strchr(arg, '=');
	if (!new_value)
		return ;
	new_value++;
	existing_len = ft_strlen(env->envp[index]);
	new_len = ft_strlen(new_value);
	result = ft_malloc((existing_len + new_len + 1), env_head);
	if (!result)
		return ;
	ft_strcpy(result, env->envp[index]);
	ft_strcat(result, new_value);
	env->envp[index] = result;
}

void	add_to_env(char *arg, t_env *env, t_list_head *env_head)
{
	int		count;
	int		i;
	char	**new_env;

	count = array_len(env->envp);
	new_env = ft_malloc(sizeof(char *) * (count + 2), env_head);
	if (!new_env)
		return ;
	i = 0;
	while (i < count)
	{
		new_env[i] = (env->envp)[i];
		i++;
	}
	new_env[count] = my_strdup(arg, env_head);
	new_env[count + 1] = NULL;
	env->envp = new_env;
}
