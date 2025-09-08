/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:47 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:29:49 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return (
		(c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
	);
}

// #include <stdio.h>
// int main (void)
// {
// 	// a tester for the function     
// 	int character = 0 ;
// 	while (character != 126)
// 	{
// 		printf("%c is alphanum : %d \n" , character, ft_isalnum(character));
// 		character++;
// 	}
//  return (0);
// }