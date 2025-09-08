/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:51:31 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/28 15:55:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	unsigned int	i ;
	unsigned int	s_len ;
	char			*substr;

	i = 0 ;
	s_len = 0 ;
	if (!s)
		return (0);
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// #include <stdio.h>

// int main(void)
// {
//     char *s = "Hello, world!";
//     char *sub = ft_substr(s, 7, 5);
//     printf("Result: %s\n", sub);
//     free(sub);
//     return 0;
// }
