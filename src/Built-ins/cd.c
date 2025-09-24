/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/24 19:09:07 by msafa            ###   ########.fr       */
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

char	*get_cd_path(char *arg, t_env *env, t_list_head *n_head)
{
	char	*path;

	if (!arg || *arg == '~')
		return (get_home_path(env));
	path = extract_quoted_path(arg, n_head);
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
		// printf("cd: memory allocation failed\n");
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