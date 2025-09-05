/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttyname.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:59:48 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:25:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    ttyname():
        return the name of the terminal device file
        that the file descriptor fd is connected to.

*/

#include <stdio.h>
#include <unistd.h>

int main () 
{
    char *name = ttyname(0);

    if (name != NULL)
    {
        printf("stdin is connected to terminal %s", name);
    }
    else
        printf("stdin is not connected to any terminal");

        return (0);
}

/*

    In minishell, ttyname can be used to find the terminal device
    name your shell is connected to, mainly for checking or 
    displaying which terminal is running the shell.

*/