/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 15:59:16 by msafa            ###   ########.fr       */
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

char	*get_cd_path(char *arg, char ***args_ptr)
{
	char	*path;

	*args_ptr = NULL;
	if (!arg)
		return (get_home_path());
	path = extract_quoted_path(arg);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_cd(char *arg)
{
	char	**args;
	char	*path;
	int		result;

	args = NULL;
	path = get_cd_path(arg, &args);
	if (!path)
	{
		printf("cd: memory allocation failed\n");
		return (1);
	}
	result = chdir(path);
	if (result == -1)
	{
		perror("cd");
		if (path && path != getenv("HOME"))
			free(path);
		return (1);
	}
	if (path && path != getenv("HOME"))
		free(path);
	return (0);
}
