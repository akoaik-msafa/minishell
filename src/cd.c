/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/21 04:44:38 by akoaik           ###   ########.fr       */
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

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*get_cd_path(char *arg, char ***args_ptr, t_env *env)
{
	char	*path;

	*args_ptr = NULL;
	if (!arg)
		return (get_home_path(env));
	path = extract_quoted_path(arg);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_cd(char *arg, t_env *env)
{
	char	**args;
	char	*path;
	char	*home_path;
	int		result;

	args = NULL;
	path = get_cd_path(arg, &args, env);
	if (!path)
	{
		printf("cd: memory allocation failed\n");
		return (1);
	}
	home_path = getenv("HOME");
	result = chdir(path);
	if (result == -1)
	{
		perror("cd");
		if (path && path != home_path)
			free(path);
		return (1);
	}// ~ is not handle it
}