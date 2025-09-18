/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 05:27:08 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_variable(const char *str, t_env *env, struct list_head *head)
{
	char	*var_name;
	char	*var_value;
	int		i;
	int		var_len;

	if (!str || str[0] != '$' || !str[1])
		return (my_strdup(str, head));
	var_name = (char *)(str + 1);
	var_len = ft_strlen(var_name);
	env->envp = get_env(env);
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, var_len) == 0 && env->envp[i][var_len] == '=')
		{
			var_value = env->envp[i] + var_len + 1;
			return (my_strdup(var_value, head));
		}
		i++;
	}
	return (my_strdup("", head));
}
