/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:28:49 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/26 11:41:03 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0 ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// #include <fcntl.h>

// int main(void)
// {
//     int fd = open("output(str).txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0)
//         return 1;

//     ft_putstr_fd("Hello 42, I'm Ali\n", fd);

//     close(fd);
//     return 0;
// }