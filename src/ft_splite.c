/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:13:01 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 21:11:16 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_tokens(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (i == 0 || (str[i - 1] == ' ' || str[i - 1] == '\t'))
				count++;
		}
		i++;
	}
	return (count);
}

static char	**allocate_tokens(int count, struct list_head *n_head)
{
	char	**tokens;

	tokens = ft_malloc((count + 1) * sizeof(char *), n_head);
	if (tokens)
		tokens[count] = NULL;
	return (tokens);
}

static void	extract_tokens(const char *str, char **tokens, int count, struct list_head *n_head)
{
	int	i;
	int	j;
	int	start;

	j = 0;
	i = 0;
	while (str[i] && j < count)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		if (start < i)
		{
			tokens[j] = ft_malloc((i - start + 1) * sizeof(char), n_head);
			if (tokens[j])
				ft_strlcpy(tokens[j], str + start, i - start + 1);
			j++;
		}
	}
}

char	**split_string(const char *str, int *count, struct list_head *n_head)
{
	char	**tokens;

	if (!str || !count)
		return (NULL);
	*count = count_tokens(str);
	if (*count == 0)
		return (NULL);
	tokens = allocate_tokens(*count, n_head);
	if (!tokens)
		return (*count = 0, NULL);
	extract_tokens(str, tokens, *count, n_head);
	return (tokens);
}
