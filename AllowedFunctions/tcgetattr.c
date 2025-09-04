/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcgetattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:44:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:46:14 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    tcgetattr():
        gets the current terminal attributes into a termios struct.

*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void)
{
    struct termios t;

    if (tcgetattr(0, &t) == 0)
        printf("Successfully got terminal attributes\n");
    else
        perror("tcgetattr");

    return (0);
}

/*

    In minishell, tcgetattr is used before tcsetattr to read
    current terminal settings, then modify them safely.

*/
