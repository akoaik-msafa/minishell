/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:39 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 15:37:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("Length of \"\": %d\n", ft_strlen(""));
// 	printf("Length of \"42\": %d\n", ft_strlen("42"));
// 	printf("Length of \"Hello, world!\": %d\n", ft_strlen("Hello, world!"));
// 	return 0;
// }