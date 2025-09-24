/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:05:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/24 19:47:32 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

char	*extract_from_quotes(char *arg, int start, int end, t_list_head *n_head)
{
	int		len;
	char	*path;

	len = end - start;
	if (len == 0)
		return (my_strdup(".", n_head));
	path = ft_malloc(len + 1, n_head);
	if (!path)
		return (NULL);
	ft_strlcpy(path, arg + start, len + 1);
	path[len] = '\0';
	return (path);
}

char	*handle_quoted_path(char *arg, int *i, t_list_head *n_head)
{
	char	quote;
	int		start;
	int		end;
	char	*path;

	quote = arg[*i];
	start = ++(*i);
	end = find_closing_quote(arg, start, quote);
	if (end == -1)
		return (my_strdup(arg, n_head));
	path = extract_from_quotes(arg, start, end, n_head);
	return (path);
}

char	*extract_quoted_path(char *arg, t_list_head *n_head, t_env *env)
{
	int		i;
	char	*home_path;
	char	*rest_path;
	char	*full_path;

	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '\0')
		return (my_strdup(".", n_head));
	if (arg[i] == '~')
	{
		home_path = get_home_path(env);
		if (!home_path)
			return (NULL);
		rest_path = arg + i + 1;
		if (*rest_path == '\0')
			return (my_strdup(home_path, n_head));
		full_path = ft_strjoin(home_path, rest_path);
		if (!full_path)
			return (NULL);
		return (full_path);
	}
	return (my_strdup(arg, n_head));
}
