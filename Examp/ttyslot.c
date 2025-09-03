/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttyslot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:40:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:28:38 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    ttyslot():
        returns the slot number of the terminal in the utmp file
        (which keeps track of logged-in users).

*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int slot = ttyslot();

    printf("This terminal slot is: %d\n", slot);

    return (0);
}

/*

    In minishell, ttyslot is rarely needed, but it can be used
    to identify which terminal session the shell is running in.

*/
