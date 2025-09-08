/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:32:15 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/28 15:43:01 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *s, const char *find, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	if (*find == '\0')
		return ((char *)s);
	i = 0;
	while (s[i] && i < len)
	{
		j = 0;
		while (s[i + j] == find[j] && (i + j) < len)
		{
			if (find[j + 1] == '\0')
				return ((char *)&s[i]);
			j++;
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     char a[] = "ali koaik     34 3 43 43 43 koaik 00p dfghsduilhfg";
//     char b[] = "ik 0";
//     char *result = ft_strnstr(a, b, 45);
//     if (result)
//         printf("Found: %s\n", result);
//     else
//         printf("Not found.\n");
//     return 0;
// }
