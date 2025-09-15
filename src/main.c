/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:23:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 15:47:35 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	init_simple_builtins(t_simple_builtin *simple_builtins)
{
	simple_builtins[0].cmd = "echo";
	simple_builtins[0].func = ft_echo;
	simple_builtins[1].cmd = "cd";
	simple_builtins[1].func = ft_cd;
	simple_builtins[2].cmd = "pwd";
	simple_builtins[2].func = ft_pwd;
	simple_builtins[3].cmd = NULL;
	simple_builtins[3].func = NULL;
}

void	init_env_builtins(t_env_builtin *env_builtins)
{
	env_builtins[0].cmd = "export";
	env_builtins[0].func = NULL;
	env_builtins[1].cmd = "unset";
	env_builtins[1].func = ft_unset;
	env_builtins[2].cmd = "env";
	env_builtins[2].func = ft_env;
	env_builtins[3].cmd = "exit";
	env_builtins[3].func = ft_exit;
	env_builtins[4].cmd = NULL;
	env_builtins[4].func = NULL;
}

int	execute_builtin(char *input, char ***env)
{
	t_simple_builtin	simple_builtins[4];
	t_env_builtin		env_builtins[5];
	char			**args;
	char			*args_str;
	int				result;

	if (!input || !input[0])
		return (0);
	args = ft_split(input);
	if (!args || !args[0])
		return (free_split(args), 0);
	init_simple_builtins(simple_builtins);
	init_env_builtins(env_builtins);
	args_str = NULL;
	if (args[1])
		args_str = join_args(args + 1);
	result = search_simple_builtins(args[0], args_str, simple_builtins) ||
			search_env_builtins(args[0], args_str, env_builtins, env);
	if (args_str)
		free(args_str);
	free_split(args);
	return (result);
}

int	search_simple_builtins(char *cmd, char *args_str, t_simple_builtin *simple_builtins)
{
	int	i;

	i = 0;
	while (simple_builtins[i].cmd)
	{
		if (ft_strcmp(cmd, simple_builtins[i].cmd) == 0)
		{
			(simple_builtins[i].func)(args_str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char ** env) 
{
	char	**env_copy;
	char	*input;

	(void)argc;
	(void)argv;
	env_copy = duplicate_env(env);
	if (!env_copy)
	{
		printf("Error: Could not duplicate environment\n");
		return (1);
	}
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
		if (!execute_builtin(input, &env_copy))
		{
			if (input[0] != '\0')
				printf("minishell: %s: command not found\n", input);
		}
		free(input);
	}
	free_env(env_copy);
	return (0);
}
