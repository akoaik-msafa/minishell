/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:38:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 05:07:42 by akoaik           ###   ########.fr       */
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

static char	*copy_env(char *src, t_list_head *head)
{
	char	*dest;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = ft_malloc(len + 1, head);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	init_env(t_env *env, char **envp, t_list_head *head)
{
	int	i;

	if (!env || !envp)
		return (0);
	env->count = count_env(envp);
	env->envp = ft_malloc((env->count + 1) * sizeof(char *), head);
	if (!env->envp)
		return (0);
	i = 0;
	while (i < env->count)
	{
		env->envp[i] = copy_env(envp[i], head);
		if (!env->envp[i])
			return (0);
		i++;
	}
	env->envp[i] = NULL;
	env->export_only = NULL;
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
