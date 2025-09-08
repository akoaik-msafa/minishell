/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:20:49 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 01:38:06 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	temp = '0' + (n % 10);
	write(fd, &temp, 1);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int fd = open("ouput(nbr).txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);
// 	if (fd < 0)
// 		return 1 ;

// 	ft_putnbr_fd(0, fd);
// 	close(fd);
// }
