/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 00:27:15 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 15:52:55 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	int_len(int n)
{
	int	i ;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	reverse_range(char *str, int start, int end)
{
	char	tmp;

	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
}

static int	fill_digits(char *str, long nb, int i)
{
	if (nb == 0)
	{
		str[i++] = '0';
		return (i);
	}
	while (nb > 0)
	{
		str[i++] = '0' + (nb % 10);
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;
	int		neg;
	long	nb;

	nb = n;
	len = int_len(n);
	str = malloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	neg = 0;
	if (nb < 0)
	{
		str[i++] = '-';
		neg = 1;
		nb = -nb;
	}
	i = fill_digits(str, nb, i);
	str[i] = '\0';
	reverse_range(str, neg, i - 1);
	return (str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*str ;
// 	str = ft_itoa(0);
// 	printf("%s", str);
// }
