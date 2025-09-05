/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:47:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:48:50 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    tgetnum():
        returns a numeric terminal capability, such as number of columns.

*/

#include <stdio.h>
#include <term.h>
#include <curses.h>

int main(void)
{
    char buffer[2048];
    tgetent(buffer, "xterm");

    int cols = tgetnum("co");
    printf("Terminal has %d columns\n", cols);

    return (0);
}

/*

    In minishell, tgetnum can be used to get terminal dimensions
    for proper line editing and cursor control.

*/
