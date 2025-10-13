/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:53:42 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 12:54:38 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	expand_export_only(char *arg, t_env *env, t_list_head *env_head)
{
	int		count;
	int		i;
	char	**new_export;

	count = array_len(env->export_only);
	new_export = ft_malloc(sizeof(char *) * (count + 2), env_head);
	if (!new_export)
		return ;
	i = 0;
	while (i < count)
	{
		new_export[i] = (env->export_only)[i];
		i++;
	}
	new_export[count] = my_strdup(arg, env_head);
	new_export[count + 1] = NULL;
	env->export_only = new_export;
}

void	add_var_no_value(char *arg, t_env *env, t_list_head *env_head)
{
	if (find_env_var(arg, env->export_only) != -1)
		return ;
	if (!env->export_only)
	{
		env->export_only = ft_malloc(sizeof(char *) * 2, env_head);
		if (!env->export_only)
			return ;
		(env->export_only)[0] = my_strdup(arg, env_head);
		(env->export_only)[1] = NULL;
		return ;
	}
	expand_export_only(arg, env, env_head);
}

int	process_export_arg(char *arg, t_data *data)
{
	int	index_env;
	int	index_export;

	if (!validate_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	index_env = find_env_var(arg, data->env->envp);
	index_export = find_env_var(arg, data->env->export_only);
	if (index_env != -1 || index_export != -1)
		handle_existing_var(arg, index_env, index_export, data);
	else
		handle_new_var(arg, data->env, data->env_head);
	return (0);
}

int	ft_export(char **args, t_data *data)
{
	char	**sorted;
	int		i;

	if (!args || !args[0])
	{
		sorted = sorted_env(data->env, data->n_head);
		if (!sorted)
			return (1);
		print_sorted(sorted);
	}
	else
	{
		i = 0;
		while (args[i])
		{
			if (process_export_arg(args[i], data))
				data->exit_code = 1;
			i++;
		}
	}
	return (data->exit_code);
}
