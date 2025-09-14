/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:23:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 11:50:30 by msafa            ###   ########.fr       */
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

int	execute_builtin(char *input, t_builtin *builtins, int nb_builtins)
{
	char	**args;
	char	*args_str;
	int		i;

	if (!input || !input[0])
		return (0);
	args = ft_split(input);
	if (!args || !args[0])
	{
		if (args)
			free_split(args);
		return (0);
	}
	i = 0;
	while (i < nb_builtins)
	{
		if (ft_strcmp(args[0], builtins[i].cmd) == 0)
		{
			if (args[1])
				args_str = join_args(args + 1);
			else
				args_str = NULL;
			(builtins[i].func)(args_str);
			if (args_str)
				free(args_str);
			free_split(args);
			return (1);
		}
		i++;
	}
	free_split(args);
	return (0);
}

int	main(int argc, char **argv, char ** env) 
{
	t_builtin	builtins[7];
	int			nb_builtins;
	char		*input;

	init_builtins(builtins);
	nb_builtins = 7;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		if (!execute_builtin(input, builtins, nb_builtins))
		{
			if (input[0] != '\0')
				printf("minishell: %s: command not found\n", input);
		}
		free(input);
	}
	return (0);
}
