/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:23:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/10 20:30:00 by msafa            ###   ########.fr       */
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
				return (1);
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

int	main(int argc, char **argv)
{
	t_builtin	builtins[7];
	int			nb_builtins;
	int			i;

	init_builtins(builtins);
	i = 0;
	nb_builtins = 7;
	if (argc < 2)
	{
		printf("Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	while (i < nb_builtins)
	{
		if (ft_strcmp(argv[1], builtins[i].cmd) == 0)
		{
			(builtins[i].func)(argv + 2);
			break ;
		}
		i++;
	}
	return (0);
}
