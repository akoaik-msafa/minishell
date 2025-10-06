/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:07:50 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/06 19:52:20 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	array_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	validate_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A'
					&& arg[i] <= 'Z') || arg[i] == '_' || (arg[i] >= '0'
					&& arg[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	find_env_var(char *var_name, char **env)
{
	int	i;
	int	len;

	if (!var_name || !env)
		return (-1);
	len = 0;
	while (var_name[len] && var_name[len] != '=' && var_name[len] != '+')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && (env[i][len] == '='
				|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *arg, t_env *env, int index, t_list_head *env_head)
{
	env->envp[index] = my_strdup(arg, env_head);
}

void	update_export(char *arg, t_env *env, int index, t_list_head *env_head)
{
	env->export_only[index] = my_strdup(arg, env_head);
}
