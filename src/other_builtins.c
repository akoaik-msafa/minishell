/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 14:11:57 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_pwd(char *arg)
{
	char	*cwd;

	(void)arg;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_export(char *arg, char **env)
{
	(void)env;
	if (arg)
		printf("export command: %s\n", arg);
	else
		printf("export command: no args\n");
	return (0);
}

int	ft_unset(char *arg, char **env)
{
	(void)env;
	if (arg)
		printf("unset command: %s\n", arg);
	else
		printf("unset command: no args\n");
	return (0);
}

int	ft_env(char *arg, char **env)
{
	int	i;

	(void)arg;
	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char *arg, char **env)
{
	(void)env;
	if (arg)
		printf("exit command: %s\n", arg);
	else
		printf("exit command: no args\n");
	return (0);
}
