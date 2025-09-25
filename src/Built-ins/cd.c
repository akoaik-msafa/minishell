/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/26 01:22:50 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// ~ is not handle it || ../ hidden files appear

char	*get_home_path(t_env *env)
{
	char	*home;

	(void)env;
	home = getenv("HOME");
	if (!home)
		printf("cd: HOME not set\n");
	return (home);
}

char	*get_cd_path(char *arg, t_env *env, t_list_head *n_head)
{
	char	*path;

	if (!arg)
	{
		return (get_home_path(env));
	}
	path = extract_quoted_path(arg, n_head, env);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_cd(char **args, t_env *env, t_list_head *n_head)
{
	char	*path;
	int		result;

	if (args[1] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	path = get_cd_path(args[0], env, n_head);
	if (!path)
	{
		return (1);
	}
	result = chdir(path);
	if (result == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}