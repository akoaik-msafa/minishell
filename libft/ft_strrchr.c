/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:29:32 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 15:53:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     char str[] = "Hello World!";
//     char *result = ft_strrchr(str, 'o');

//     if (result != NULL)
//         printf("Last occurrence of 'o': %s\n", result);
//     else
//         printf("Character not found.\n");

//     return 0;
// }