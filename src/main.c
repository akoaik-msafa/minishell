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

int	process_echo_options(char **args)
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
	return (option);
}

void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_echo(char *arg)
{
	char	**args;
	int		option;
	int		start_index;

	if (!arg)
	{
		printf("\n");
		return (0);
	}
	args = ft_split(arg);
	if (!args)
		return (1);
	option = process_echo_options(args);
	start_index = 0;
	while (args[start_index] && check_options(args[start_index]))
		start_index++;
	print_echo_args(args, start_index);
	if (!option)
		printf("\n");
	free_split(args);
	return (0);
}

int	calculate_total_length(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

void	copy_args_to_result(char **args, char *result)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (args[i])
	{
		strcpy(result + pos, args[i]);
		pos += strlen(args[i]);
		if (args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	result[pos] = '\0';
}

char	*join_args(char **args)
{
	int		total_len;
	char	*result;

	if (!args || !args[0])
		return (NULL);
	total_len = calculate_total_length(args);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	copy_args_to_result(args, result);
	return (result);
}

int	main(int argc, char **argv)
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
