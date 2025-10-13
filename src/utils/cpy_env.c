/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:38:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 16:58:22 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

int	init_env(t_env *env, char **envp, t_list_head *head)
{
	if (!env || !envp)
		return (0);
	env->count = count_env(envp);
	if (!init_envp_array(env, envp, head))
		return (0);
	if (!init_export_array(env, head))
		return (0);
	handle_shlvl_init(env, head);
	return (1);
}

char	**get_env(t_env *env)
{
	if (!env->envp)
		return (NULL);
	return (env->envp);
}

int	get_env_count(t_env *env)
{
	if (!env)
		return (0);
	return (env->count);
}
