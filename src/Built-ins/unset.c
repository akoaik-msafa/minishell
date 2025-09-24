/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:48:37 by msafa             #+#    #+#             */
/*   Updated: 2025/09/24 18:47:23 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_unset(char **args, t_env *env)
{
	int index;
    int i;

    i = 0;
	if(!args || !env)
		return(-1);
    while(args[i])
    {
        index = find_env_var(args[i],env->envp);
        if(index != -1)
        {
            free(env->envp[index]);
            while(env->envp[index + 1])
            {
                env->envp[index] = env->envp[index + 1];
                index++;
            }
            env->envp[index] = NULL;
        }
        if(env->export_only)
        {
            index = find_env_var(args[i],env->export_only);
            if(index != -1)
            {
                free(env->export_only[index]);
                while(env->export_only[index + 1])
                {
                    env->export_only[index] = env->export_only[index + 1];
                    index++;
                }
                env->export_only[index] = NULL;
            }
        }
        i++;
    }
	return(0);
}
