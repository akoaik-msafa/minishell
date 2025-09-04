/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetflag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:46:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 22:08:02 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    tgetflag():
        checks if a terminal capability flag is present.

*/

#include <stdio.h>
#include <term.h>

int main(void)
{
    char buffer[2048];
    tgetent(buffer, "xterm");

    if (tgetflag("am"))
        printf("Terminal supports automatic margins\n");
    else
        printf("Terminal does not support automatic margins\n");

    return (0);
}

/*

    In minishell, tgetflag can be used to detect specific
    terminal capabilities (like auto-wrap support).

*/
