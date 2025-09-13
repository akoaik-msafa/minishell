/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:38:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/13 23:38:48 by akoaik           ###   ########.fr       */
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

static char	*copy_env_string(const char *src, struct list_head *head)
{
	char	*dst;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = ft_malloc(len + 1, head);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	init_env(t_env *env, char **envp, struct list_head *head)
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
		env->envp[i] = copy_env_string(envp[i], head);
		if (!env->envp[i])
			return (0);
		i++;
	}
	env->envp[i] = NULL;
	return (1);
}

char	**get_env(t_env *env)
{
	if (!env)
		return (NULL);
	return (env->envp);
}

int	get_env_count(t_env *env)
{
	if (!env)
		return (0);
	return (env->count);
}