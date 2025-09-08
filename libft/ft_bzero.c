/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:36 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:29:39 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *s, unsigned int n)
{
	unsigned char		*ptr;
	unsigned int		i;

	ptr = (unsigned char *) s ;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// int	main(void)
// {
// 	char s[] = "123456789alikoaik";
// 	ft_bzero(s,4);
// 	for(int i = 0 ; i < 17 ; i++)
// 	{
// 		printf("%c\n",s[i]);
// 	}
// 	reƒturn (0);
// }
