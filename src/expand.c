/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/22 03:26:59 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_variable(const char *str, t_env *env, struct list_head *head)
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	char	*result;
	int		i;
	int		j;
	int		var_len;
	int		total_len;

	j = 0;
	
	// check if str is empty
	if(!str)
		return (my_strdup("", head));

	// prefix part
	while(str[j] && str[j] != '$')
			j++;
	if (!str[j])
		return (my_strdup(str, head));
	prefix = ft_malloc(((j + 1) * sizeof(char)),head);
	ft_strlcpy(prefix,str,j + 1);

	//expanded part (from $ till whitespace found or end of string)
	var_name = (char *)(str + j + 1); // hon mn 7ad $ d8re

	// hl2 bdna njib toul sah mn $ w tlou3
	var_len = 0;
	while (var_name[var_len] && var_name[var_len] != ' ' && var_name[var_len] != '\t')
    	var_len++;
	suffix =  var_name + var_len;
	// halla bdna naamelo expansion nerjaa nshuf shu be2e la ekhir shi nejma3on w neb3aton kelon msh  bs lexpansion value
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, var_len) == 0 && env->envp[i][var_len] == '=')
		{
			var_value = env->envp[i] + var_len + 1;
			total_len = ft_strlen(prefix) + ft_strlen(suffix) + ft_strlen(var_value);
			result = ft_malloc((total_len + 1) * sizeof(char),head);
			if(!result)
				return(NULL);
			ft_strcpy(result,prefix);
			ft_strlcat(result,var_value,total_len + 1);
			ft_strlcat(result,suffix,total_len + 1);
			return(result);
		}
		i++;
	}
	return (my_strdup("", head));
}
