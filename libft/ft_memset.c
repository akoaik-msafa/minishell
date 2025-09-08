/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:18 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:31:19 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned int		i ;
	unsigned char		*ptr ;

	i = 0 ;
	ptr = (unsigned char *) b;
	while (i < len)
	{
		ptr[i] = (unsigned char) c ;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char	*buff;
// 	char	*my_buff;

// 	buff = malloc(20);
// 	my_buff = malloc(20);

// 	if (!buff || !my_buff)
// 		return (1);

// 	// fill the two buffers : 
// 	ft_memset(buff,760,20);
// 	ft_memset(my_buff,'A',20);

// 	ft_memset(buff,'X',10);
// 	ft_memset(my_buff,'S',12);

// 	// printing : 

// 	printf("buff : ");
// 	int i = 0 ;
// 	while (i < 20)
// 	{
// 		printf("%c",buff[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0 ; 
// 	while (i < 20)
// 	{
// 		printf("%c",my_buff[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(buff);
// 	free(my_buff);
// }
