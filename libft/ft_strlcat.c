/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:36:25 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/20 17:36:57 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int dstsize)
{
	unsigned int	i ;
	unsigned int	j ;

	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

// #include <stdio.h>
// int main(void)
// {
// 	char buffer[20] = "Hello";
// 	const char *src = " World!";
// 	unsigned int result;

// 	result = ft_strlcat(buffer, src, sizeof(buffer));

// 	printf("After strlcat:\n");
// 	printf("Buffer: \"%s\"\n", buffer);
// 	printf("Return value: %u\n", result);

// 	return 0;
// }