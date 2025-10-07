/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:21:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/07 19:44:20 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*my_strdup(const char *s1, struct list_head *n_head)
{
	int		len;
	char	*copy;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	copy = ft_malloc(sizeof(char) * (len + 1), n_head);
	if (!copy)
		return (0);
	i = 0;
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
