/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:23:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/13 18:58:30 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	init_builtins(t_builtin *builtins)
{
	builtins[0].cmd = "echo";
	builtins[0].func = ft_echo;
	builtins[1].cmd = "cd";
	builtins[1].func = ft_cd;
	builtins[2].cmd = "pwd";
	builtins[2].func = ft_pwd;
	builtins[3].cmd = "export";
	builtins[3].func = ft_export;
	builtins[4].cmd = "unset";
	builtins[4].func = ft_unset;
	builtins[5].cmd = "env";
	builtins[5].func = ft_env;
	builtins[6].cmd = "exit";
	builtins[6].func = ft_exit;
}

int	main(int argc, char **argv, char ** env) // copy the ENV to a 2 dimention to you can edit it and export to it :)
{
	t_builtin	builtins[7];
	int			nb_builtins;
	int			i;
	char		*args_str;

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
			args_str = join_args(argv + 2);
			(builtins[i].func)(args_str);
			if (args_str)
				free(args_str);
			break ;
		}
		i++;
	}
	return (0);
}
