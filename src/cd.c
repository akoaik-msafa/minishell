/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 12:12:30 by msafa            ###   ########.fr       */
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

char	*extract_from_quotes(char *arg, int start, int end)
{
	int		len;
	char	*path;

	len = end - start;
	if (len == 0)
		return (ft_strdup("."));
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, arg + start, len);
	path[len] = '\0';
	return (path);
}

int	find_closing_quote(char *arg, int start, char quote)
{
	int	i;

	i = start;
	while (arg[i] && arg[i] != quote)
		i++;
	if (arg[i] == quote)
		return (i);
	return (-1);
}

char	*handle_quoted_path(char *arg, int *i)
{
	char	quote;
	int		start;
	int		end;
	char	*path;

	quote = arg[*i];
	start = ++(*i);
	end = find_closing_quote(arg, start, quote);
	if (end == -1)
		return (ft_strdup(arg));
	path = extract_from_quotes(arg, start, end);
	return (path);
}

char	*extract_quoted_path(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '"' || arg[i] == '\'')
		return (handle_quoted_path(arg, &i));
	if (arg[i] == '\0')
		return (ft_strdup("."));
	return (ft_strdup(arg));
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