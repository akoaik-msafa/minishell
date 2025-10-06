/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:50:40 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/02 23:40:19 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_data *data)
{
	long	exit_code;

	if (!args || !args[0])
		exit(data->exit_code);
	if (args[1])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (!is_numeric(args[0]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	exit_code = ft_atoi(args[0]);
	exit((unsigned char)(exit_code % 256));
}
