/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:15:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/18 02:27:16 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	search_env_builtins(char *cmd, char *args_str,
		t_env_builtin *env_builtins, t_env_data *env_data)
{
	int	i;

	i = 0;
	while (env_builtins[i].cmd)
	{
		if (ft_strcmp(cmd, env_builtins[i].cmd) == 0)
		{
			(env_builtins[i].func)(args_str, env_data);
			return (1);
		}
		i++;
	}
	return (0);
}
