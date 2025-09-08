/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:30:10 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:30:12 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// #include <stdio.h>
// int main (void)
// {
//     int character = 0 ;
//     while (character != 127)
//     {
//         printf("%c is digigt : %d\n",character,ft_isdigit(character));
//         character++;
//     }
//     return (0);
// }