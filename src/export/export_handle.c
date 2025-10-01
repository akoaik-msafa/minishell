/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:13:19 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/01 04:13:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void print_sorted(char **sorted)
{
    int i;
    char *equal_pos;

    i = 0;
    while (sorted[i])
    {
        equal_pos = ft_strchr(sorted[i],'=');
        if(equal_pos)
        {
            *equal_pos = '\0';
            printf("declare -x %s=\"%s\"\n",sorted[i],equal_pos + 1);
            *equal_pos = '=';
        }
        else
            printf("declare -x %s\n", sorted[i]);
        i++;
    }
}

void handle_existing_var(char *arg, t_env *env, int index, t_list_head *env_head)
{
    int i;

    i = 0;
    while(arg[i] && arg[i] != '=')
        i++;
    if (arg[i] == '=' && i > 0 && arg[i - 1] == '+')
        append_to_env(arg, env, index, env_head);
    else if (arg[i] == '=')
        update_env(arg, env, index, env_head);
}

void handle_new_var(char *arg, t_env *env, t_list_head *env_head)
{
    int i;
    int index;

    i = 0;
    while(arg[i] && arg[i] != '=')
        i++;
    if (arg[i] == '=')
    {
        index = find_env_var(arg, env->export_only);
        if(index != -1)
        {
            while(env->export_only[index + 1])
            {
                env->export_only[index] = env->export_only[index + 1];
                index++;
            }
            env->export_only[index] = NULL;
        }
        add_to_env(arg, env, env_head);
        add_to_export_only(arg, env, env_head);
    }
    else
        add_var_no_value(arg, env, env_head);
}