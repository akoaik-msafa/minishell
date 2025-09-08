/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:28 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:31:30 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0 ;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     const char *str = "Hello, world!";
//     char *result = ft_strchr(str, 'd');
//     if (result)
//         printf("Found: %s\n", result);
//     else
//         printf("Character not found.\n");
//     return 0;
// }