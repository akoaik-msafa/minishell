/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetnum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:47:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/04 01:01:18 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    tgetnum():
        Returns a numeric terminal capability, such as the number of columns
        or lines in the terminal. Useful for controlling cursor movement,
        formatting output, or implementing features like line editing in 
        shell programs (e.g., minishell).

*/

#include <stdio.h>
#include <term.h>

int main(void)
{
    // 2048 is a typical size large enough to hold most terminfo entries.
    char buffer[2048];

    /* "xterm" is the name of the terminal type.
     	It tells tgetent which terminal capabilities to load. 
   	 	You can replace it with "vt100", "linux", etc. depending on your terminal. */
	
    tgetent(buffer, "xterm");

    // tgetnum("co") retrieves the number of columns for the current terminal.
    int cols = tgetnum("co");

    printf("Terminal has %d columns\n", cols);

    return (0);
}

 /* Usage in minishell: get terminal size for line editing and cursor control */
