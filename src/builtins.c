/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:30:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/10 23:21:53 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_cd(char **args)
{
	char	*path;
	char	*home;

	if (!args || !args[0])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_pwd(char **args)
{
	(void)args;
	printf("pwd command\n");
	return (0);
}

int	ft_export(char **args)
{
	if (args[0])
		printf("export command: %s\n", args[0]);
	else
		printf("export command: no args\n");
	return (0);
}

int	ft_unset(char **args)
{
	if (args[0])
		printf("unset command: %s\n", args[0]);
	else
		printf("unset command: no args\n");
	return (0);
}

int	ft_env(char **args)
{
	(void)args;
	printf("env command\n");
	return (0);
}
