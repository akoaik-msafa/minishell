/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:02 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/28 15:53:53 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	const unsigned char		*ptr1 ;
	const unsigned char		*ptr2 ;
	unsigned int			i;

	i = 0;
	ptr1 = (const unsigned char *) s1 ;
	ptr2 = (const unsigned char *) s2 ;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
//
// int main(void)
// {
//    char a [] = "Hello A";
//    char b [] = "Hello Z" ;
//
//    int diff = ft_memcmp(a,b,7);
//    printf("result = %d\n",diff);
//    return (0);
// }
