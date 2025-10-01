/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/01 05:19:04 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_export_array(t_env *env, t_list_head *head)
{
	int	i;

	env->export_only = ft_malloc(sizeof(char *) * (env->count + 1), head);
	if (!env->export_only)
		return (0);
	i = 0;
	while (i < env->count)
	{
		env->export_only[i] = my_strdup(env->envp[i], head);
		i++;
	}
	env->export_only[env->count] = NULL;
	return (1);
}

char	*create_shlvl_entry(char *new_shlvl_str, t_list_head *head)
{
	char	*new_entry;

	new_entry = ft_malloc(ft_strlen("SHLVL=") + ft_strlen(new_shlvl_str) + 1,
			head);
	if (new_entry)
	{
		ft_strcpy(new_entry, "SHLVL=");
		ft_strcat(new_entry, new_shlvl_str);
	}
	return (new_entry);
}

void	update_shlvl_entries(t_env *env, int env_index, int export_index,
		char *new_shlvl_str, t_list_head *head)
{
	char	*new_env_entry;
	char	*new_export_entry;

	new_env_entry = create_shlvl_entry(new_shlvl_str, head);
	if (new_env_entry)
		env->envp[env_index] = new_env_entry;
	if (export_index != -1)
	{
		new_export_entry = create_shlvl_entry(new_shlvl_str, head);
		if (new_export_entry)
			env->export_only[export_index] = new_export_entry;
	}
	else
	{
		new_export_entry = create_shlvl_entry(new_shlvl_str, head);
		if (new_export_entry)
			add_to_export_only(new_export_entry, env, head);
	}
}

void	handle_shlvl_init(t_env *env, t_list_head *head)
{
	int		env_index;
	int		export_index;
	int		current_shlvl;
	char	*new_shlvl_str;

	env_index = find_env_var("SHLVL", env->envp);
	export_index = find_env_var("SHLVL", env->export_only);
	if (env_index == -1)
	{
		add_to_env("SHLVL=1", env, head);
		add_to_export_only("SHLVL=1", env, head);
	}
	else
	{
		current_shlvl = ft_atoi(env->envp[env_index] + 6);
		new_shlvl_str = ft_itoa_with_head(current_shlvl + 1, head);
		update_shlvl_entries(env, env_index, export_index, new_shlvl_str,
			head);
	}
}

void	add_to_export_only(char *arg, t_env *env, t_list_head *env_head)
{
	int		count;
	int		i;
	char	**new_export;

	count = 0;
	while (env->export_only && env->export_only[count])
		count++;
	new_export = ft_malloc(sizeof(char *) * (count + 2), env_head);
	if (!new_export)
		return ;
	i = 0;
	while (i < count)
	{
		new_export[i] = env->export_only[i];
		i++;
	}
	new_export[count] = copy_env(arg, env_head);
	new_export[count + 1] = NULL;
	env->export_only = new_export;
}
