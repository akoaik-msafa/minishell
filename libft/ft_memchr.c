/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:30:28 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/28 15:53:17 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned char	*ptr;
	unsigned int	i;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char) c)
		{
			return (&ptr[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
//
// // void *ft_memchr(const void *s, int c, size_t n);
//
// int main(void)
// {
//     const char data[] = "42 Network Libft Test";
//
//     printf("Case 1: %s\n", (char *)ft_memchr(data, 'N', strlen(data)));
//
//     printf("Case 2: %s\n", (char *)ft_memchr(data, '4', strlen(data)));
//
//     printf("Case 3: %s\n", (char *)ft_memchr(data, 't', strlen(data)));
//
//     printf("Case 4: %s\n", (char *)ft_memchr(data, 'z', strlen(data)));
//
//     printf("Case 5: %s\n", (char *)ft_memchr(data, '\0', strlen(data)));
//
//     printf("Case 6: %s\n", (char *)ft_memchr(data, 'N', 0));
//     return 0;
// }
