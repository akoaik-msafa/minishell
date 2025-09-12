/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:42:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/03 21:35:43 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    getenv():
        returns the value of an environment variable by name.

*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *path = getenv("PATH");

    if (path != NULL)
        printf("PATH: %s\n", path);
    else
        printf("PATH variable not found\n");

    return (0);
}

/*

    In minishell, getenv is used to read environment variables
    like PATH, HOME, and USER, which are critical for commands.

*/
