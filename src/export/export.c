/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:53:42 by msafa             #+#    #+#             */
/*   Updated: 2025/09/30 02:00:40 by msafa            ###   ########.fr       */
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

void add_var_no_value(char *arg, t_env *env, t_list_head *env_head)
{
	if (find_env_var(arg, env->export_only) != -1)
		return;
	if (!env->export_only)
	{
		env->export_only = ft_malloc(sizeof(char *) * 2, env_head);
		if (!env->export_only)
			return;
		(env->export_only)[0] = my_strdup(arg, env_head);
		(env->export_only)[1] = NULL;
		return;
	}
	expand_export_only(arg, env, env_head);
}

int process_export_arg(char *arg, t_env *env, t_list_head *env_head)
{
    int index;

    if (!validate_identifier(arg))
    {
        write(2,"minishell: export: ", 20);
        printf("`%s': not a valid identifier\n", arg);
        return (0);
    }
    index = find_env_var(arg, env->envp);
    if (index != -1)
        handle_existing_var(arg, env, index, env_head);
    else
        handle_new_var(arg, env, env_head);
    return (1);
}

int ft_export(char **args,t_env *env,t_list_head *n_head,t_list_head *env_head)
{
    char    **sorted;
    int     i;
    
    if (!args || !args[0])
	{
        sorted = sorted_env(env,n_head);
        if (!sorted)
            return (1);
        print_sorted(sorted);
    }
    else
    {
        i = 0;
        while(args[i])
        {
            if (!process_export_arg(args[i], env, env_head))
                return (0);
            i++;
        }
    }
    return (0);
}
