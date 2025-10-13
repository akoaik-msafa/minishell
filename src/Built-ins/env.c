/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:17:18 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 12:57:40 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_env(char **arg, t_env *env)
{
	int	i;

	(void)arg;
	if (!env || !env->envp)
	{
		printf("minishell: env: No such file or directory\n");
		return (-1);
	}
	i = 0;
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}
