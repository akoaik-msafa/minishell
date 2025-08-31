/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:38:01 by akoaik            #+#    #+#             */
/*   Updated: 2025/08/31 21:43:51 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	strerror() : is a function that converts an error number
	into a human-readable message.

*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("no_file.txt", O_RDONLY);

    if (fd == -1)
    {
        printf("Error: %s\n", strerror(errno)); /*
		-->  errno is a global variable in C that stores the error
			 code of the last failed system or library call. */
    }
    else
    {
        close(fd);
    }

    return 0;
}
