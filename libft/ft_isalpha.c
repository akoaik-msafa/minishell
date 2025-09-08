/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:53 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/19 17:29:55 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
	{
		return (1);
	}
	else
		return (0);
}

// #include <stdio.h>
// int main (void)
// {
// 	// a tester for the function     
// 	int character = 0 ;
// 	while (character != 126)
// 	{
// 		printf("%c is alphabet : %d \n" , character, ft_isalpha(character));
// 		character++;
// 	}
//  return (0);
// }