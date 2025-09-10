/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:30:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/10 20:30:00 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

int	ft_exit(char **args)
{
	if (args[0])
		printf("exit command: %s\n", args[0]);
	else
		printf("exit command: no args\n");
	return (0);
}

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
