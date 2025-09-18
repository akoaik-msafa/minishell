/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:13:01 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/17 22:35:19 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_tokens(const char *str)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (!in_quotes && (str[i] == '"' || str[i] == '\''))
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t')
				count++;
			quote_char = str[i];
			in_quotes = 1;
		}
		else if (in_quotes && str[i] == quote_char)
			in_quotes = 0;
		else if (!in_quotes && str[i] != ' ' && str[i] != '\t')
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t')
				count++;
		}
		i++;
	}
	return (count);
}

static void	extract_tokens(const char *str, char **tokens, int count,
		t_list_head *n_head)
{
	int		i, j, start, len;
	char	quote_char;

	i = 0;
	j = 0;
	while (str[i] && j < count)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		start = i;
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_char = str[i++];
			start = i;
			while (str[i] && str[i] != quote_char)
				i++;
			len = i - start;
			if (str[i] == quote_char)
				i++;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '"'
				&& str[i] != '\'')
				i++;
			len = i - start;
		}
		if (len > 0)
		{
			tokens[j] = ft_malloc((len + 1) * sizeof(char), n_head);
			if (tokens[j])
				ft_strlcpy(tokens[j], str + start, len + 1);
			j++;
		}
	}
}

char	**split_string(const char *str, int *count, t_list_head *n_head)
{
	char	**tokens;

	if (!str || !count)
		return (NULL);
	*count = count_tokens(str);
	if (*count == 0)
		return (NULL);
	tokens = ft_malloc((*count + 1) * sizeof(char *), n_head);
	if (!tokens)
		return (*count = 0, NULL);
	tokens[*count] = NULL;
	extract_tokens(str, tokens, *count, n_head);
	return (tokens);
}
