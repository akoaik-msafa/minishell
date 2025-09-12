/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcsetattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:43:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:41:57 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    tcsetattr():
        sets the terminal attributes (like echoing, canonical mode).

*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void)
{
	// a structure that holds terminal settings
    struct termios t;

    tcgetattr(0, &t);        // get current settings
    t.c_lflag &= ~ECHO;      // disable echo
    tcsetattr(0, TCSANOW, &t);

    printf("Type something (it will not be echoed): ");
    getchar();

    return (0);
}

/*

    In minishell, tcsetattr can be used to configure terminal
    behavior (like disabling Ctrl-C output or command echo).

*/
