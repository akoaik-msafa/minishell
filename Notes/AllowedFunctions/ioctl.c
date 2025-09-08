/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:41:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:29:45 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    ioctl():
        performs low-level control operations on devices.
        Commonly used on terminals to get or set settings,
        like the window size.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void)
{
    struct winsize w;

    if (ioctl(1, TIOCGWINSZ, &w) == 0)
        printf("Terminal size: %d rows, %d cols\n", w.ws_row, w.ws_col);
    else
        perror("ioctl");

    return (0);
}

/*

    In minishell, ioctl can be used to get the terminal window
    size for proper cursor movement and display formatting.

*/
