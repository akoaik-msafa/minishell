/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:57:19 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/26 11:40:35 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <fcntl.h>
// int	main(void)
// {
// 	int fd = open("output(char).txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	// Write only , Create if does't exist , empty it
//  // 0644 owner: read write , group: read , others : read only 
// 	// --> like chmod: rw-r--r--
// 	if (fd < 0)
// 		return (1);

// 	ft_putchar_fd('H', fd);
// 	ft_putchar_fd('i', fd);
// 	ft_putchar_fd('\n', fd);

// 	close(fd);
// 	return (0);	
// }