/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:10:25 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/01 04:12:13 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	swap_strings(char **str, int j)
{
	char	*temp;

	temp = str[j];
	str[j] = str[j + 1];
	str[j + 1] = temp;
}

char	**bubble_sorting(char **str, t_env *env)
{
	int	i;
	int	j;
	int	total;

	if (env->export_only)
		total = array_len(env->export_only);
	else
		total = 0;
	i = 0;
	while (i < total)
	{
		j = 0;
		while (j < total - i - 1)
		{
			if (ft_strcmp(str[j], str[j + 1]) > 0)
				swap_strings(str, j);
			j++;
		}
		i++;
	}
	return (str);
}

char **sorted_env(t_env *env,t_list_head *n_head)
{
    char    **str;
    int     export_count;
    int     i;

    if (env->export_only)
        export_count = array_len(env->export_only);
    else
        export_count = 0;
    str = ft_malloc(sizeof(char *) * (export_count + 1),n_head);
    if (!str)
        return (NULL);
    i = 0;
    while (i < export_count)
    {
        str[i] = (env->export_only)[i];
        i++;
    }
	str[export_count] = NULL;
    str = bubble_sorting(str,env);
    return(str);
}
