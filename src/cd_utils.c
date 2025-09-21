/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:05:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/20 17:40:18 by akoaik           ###   ########.fr       */
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
	ft_strlcpy(path, arg + start, len + 1);
	path[len] = '\0';
	return (path);
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
