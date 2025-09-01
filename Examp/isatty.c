/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:50:45 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/01 22:07:46 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	isatty() : 
		checks if the file descriptor is connected 
		to a terminal
		if yes it return 1 
		if no it return 0

*/

#include <stdio.h>
#include <unistd.h>

int main (void)
{
	if (isatty(0))
	{
		printf("stdin is form a terminal (keyboard.) \n");
	}
	else
	{
		printf("stdin is NOT a terminal (maybe file or pipe). \n");
	}
	return 0 ;
}

/*

	try ./a.out 
	and try 
		./a.out < anyfile
*/