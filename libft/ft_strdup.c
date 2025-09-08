/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:40:56 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/21 11:48:29 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	copy = (char *)malloc(sizeof(char) * (len + 1));
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

// #include <stdio.h>
// int	main(void)
// {
// 	const char *original = "42 Network";
// 	char *copy;

// 	copy = ft_strdup(original);
// 	if (!copy)
// 	{
// 		printf("Memory allocation failed");
// 		return (1);
// 	}
// 	printf("Original: %s\n", original);
// 	printf("Copy:     %s\n", copy);
// 	free(copy);
// 	return (0);
// }
