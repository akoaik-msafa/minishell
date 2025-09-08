/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:13 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:31:15 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dst, const void *src, unsigned int n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	unsigned int	i;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (ptr_dst);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	int	*std_buf = malloc(5 * sizeof(int));
// 	int	*my_buf = malloc(5 * sizeof(int));
//     int src[] = {42,21,65,4,8,0,45,3};

// 	if (!std_buf || !my_buf)
// 		return (1);

//     for (int i = 0; i < 5; i++)
//         std_buf[i] = src[i];

// 	ft_memcpy(my_buf, src, 5 * sizeof(int));

// 	for (int i = 0; i < 5; i++)
// 	{
// 		printf("Standard %d : %d | ft_memcpy %d : %d\n",
// 			i, std_buf[i], i, my_buf[i]);
// 	}

// 	free(std_buf);
// 	free(my_buf);
// 	return (0);
// }
