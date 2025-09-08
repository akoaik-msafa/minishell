/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:17:28 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 15:38:31 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*result;

	if (!s || !f)
		return (0);
	i = 0;
	result = (char *)malloc(ft_strlen(s) + 1);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char odd_changer(unsigned int a, char c)
// {
// 	int num = c - '0';
// 	if (num % 2 == 0)
// 		return c;
// 	else
// 		return ('*');
// }

// #include <stdio.h>

// int main(void)
// {
// 	char *str = "0123456789";
// 	char *mapped = ft_strmapi(str, odd_changer);
// 	if (mapped)
// 	{
// 		printf("%s\n", mapped);
// 		free(mapped);
// 	}
// 	return 0;
// }