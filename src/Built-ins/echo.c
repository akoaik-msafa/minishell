/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/10/05 18:00:40 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	calculate_total_length(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += ft_strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

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
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	option;
	int	start_index;

	if (!args || !args[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	option = process_echo_options(args);
	start_index = 0;
	while (args[start_index] && check_options(args[start_index]))
		start_index++;
	print_echo_args(args, start_index);
	if (!option)
		write(1, "\n", 1);
	return (0);
}
