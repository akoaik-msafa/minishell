/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:48:37 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 13:02:18 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	remove_env_var(char *var_name, char **env_array)
{
	int	index;

	index = find_env_var(var_name, env_array);
	if (index != -1)
	{
		free(env_array[index]);
		while (env_array[index + 1])
		{
			env_array[index] = env_array[index + 1];
			index++;
		}
		env_array[index] = NULL;
	}
}

int	ft_unset(char **args, t_env *env)
{
	int	i;

	i = 0;
	if (!args || !env)
		return (-1);
	while (args[i])
	{
		remove_env_var(args[i], env->envp);
		if (env->export_only)
			remove_env_var(args[i], env->export_only);
		i++;
	}
	return (0);
}
