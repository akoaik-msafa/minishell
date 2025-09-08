/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:23:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/08 20:40:50 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	check_options(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
			if (arg[i] == '\0')
			{
				return (1);
			}
		}
	}
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	while (args[i] && check_options(args[i]))
	{
		option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	main(int argc, char **argv)
{
	int			nb_builtins;
	int			i;
	char *array[7];

	built_ins[7];
	{{"echo", ft_echo}
	};

	i = 0;
	nb_builtins = sizeof(built_ins) / sizeof(built_ins[0]);
	while (i < nb_builtins)
	{
		if (ft_strcmp(argv[1], built_ins[i].cmd) == 0)
		{
			(built_ins[i].func)(argv + 2);
			break ;
		}
		i++;
	}
	return (0);
}
