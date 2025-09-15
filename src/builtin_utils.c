/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:15:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 15:43:46 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	search_env_builtins(char *cmd, char *args_str,
		t_env_builtin *env_builtins, char ***env)
{
	int	i;

	i = 0;
	while (env_builtins[i].cmd)
	{
		if (ft_strcmp(cmd, env_builtins[i].cmd) == 0)
		{
			if (ft_strcmp(cmd, "export") == 0)
				ft_export(args_str, env);
			else
				(env_builtins[i].func)(args_str, *env);
			return (1);
		}
		i++;
	}
	return (0);
}
