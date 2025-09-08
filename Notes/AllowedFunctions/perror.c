/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:46:14 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/01 11:49:20 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	perror():
		function that prints a human-readable error message 
		to standard error.
		
		It automatically uses the global variable errno to
		know what went wrong.

*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) 
{
    // Try to open a file that does not exist
    int fd = open("no_file.txt", O_RDONLY);

    if (fd == -1) {
        // perror prints: your message + system error message
        perror("open");
    }

    return 0;
}
