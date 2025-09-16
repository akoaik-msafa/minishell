/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/16 21:42:43 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_variable(const char *str, t_env *env, struct list_head *head)
{
	char	*var_name;
	char	*var_value;
	char	**envp;
	int		i;
	int		var_len;

	if (!str || str[0] != '$' || !str[1])
		return (my_strdup(str, head));
	var_name = (char *)(str + 1);
	var_len = ft_strlen(var_name);
	envp = get_env(env);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var_name, var_len) == 0 && envp[i][var_len] == '=')
		{
			var_value = envp[i] + var_len + 1;
			return (my_strdup(var_value, head));
		}
		i++;
	}
	return (my_strdup("", head));
}