/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 05:18:29 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 17:00:58 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*copy_env(char *src, t_list_head *head)
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

char	*ft_itoa_with_head(int n, t_list_head *head)
{
	char	*temp;
	char	*result;

	temp = ft_itoa(n);
	if (!temp)
		return (NULL);
	result = copy_env(temp, head);
	free(temp);
	return (result);
}

int	init_envp_array(t_env *env, char **envp, t_list_head *head)
{
	int	i;

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
	return (1);
}
