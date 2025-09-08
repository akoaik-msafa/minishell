/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:57:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 16:51:28 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbele, size_t size)
{
	size_t				i;
	unsigned char		*ptr;

	i = 0;
	if (nbele == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nbele > SIZE_MAX / size)
		return (0);
	ptr = (unsigned char *)malloc(nbele * size);
	if (!ptr)
		return (0);
	while (i < nbele * size)
		ptr[i++] = 0;
	return ((void *)ptr);
}

// #include <stdio.h>
// int main (void)
// {
// 	char *buff = (char *)ft_calloc(2,(sizeof(char) * 5));
// 	printf("%s",buff);
// 	return (0);
// }
