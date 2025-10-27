/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:54:13 by msafa             #+#    #+#             */
/*   Updated: 2025/10/27 22:54:30 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*remove_backslash_escapes(const char *str, t_data *data)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	result = ft_malloc((len + 1) * sizeof(char), data->n_head);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			result[j++] = '$';
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
