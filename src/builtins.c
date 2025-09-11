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

char	*get_home_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		printf("cd: HOME not set\n");
	return (home);
}

char	*get_cd_path(char *arg, char ***args_ptr)
{
	char	**args;
	char	*path;
	char	*home;

	if (!arg)
		return (get_home_path());
	args = ft_split(arg);
	*args_ptr = args;
	if (!args || !args[0])
	{
		home = get_home_path();
		if (!home && args)
			free_split(args);
		return (home);
	}
	path = args[0];
	return (path);
}

int	ft_cd(char *arg)
{
	char	**args;
	char	*path;

	args = NULL;
	path = get_cd_path(arg, &args);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		if (args)
			free_split(args);
		return (1);
	}
	if (args)
		free_split(args);
	return (0);
}

int	ft_pwd(char *arg)
{
	(void)arg;
	printf("pwd command\n");
	return (0);
}

int	ft_export(char *arg)
{
	if (arg)
		printf("export command: %s\n", arg);
	else
		printf("export command: no args\n");
	return (0);
}

int	ft_unset(char *arg)
{
	if (arg)
		printf("unset command: %s\n", arg);
	else
		printf("unset command: no args\n");
	return (0);
}

int	ft_env(char *arg)
{
	(void)arg;
	printf("env command\n");
	return (0);
}
