/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:56 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/25 20:53:26 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static unsigned int	totl_len(const char *s1, const char *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2));
}

char	*my_strjoin(char const *s1, char const *s2, t_list_head *n_head)
{
	unsigned int i;
	unsigned int j;
	char *result;

	if (!s1 || !s2)
		return (0);
	result = (char *)ft_malloc(totl_len(s1, s2) + 1, n_head);
	if (!result)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}