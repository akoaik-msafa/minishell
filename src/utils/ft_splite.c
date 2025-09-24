/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:13:01 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/22 16:46:59 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_operator(char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
		return (2);
	if (c1 == '>' && c2 == '>')
		return (2);
	if (c1 == '|' || c1 == '<' || c1 == '>')
		return (1);
	return (0);
}

static int	count_tokens(const char *str)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;
	int		op_len;

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
		else if (!in_quotes && (op_len = is_operator(str[i], str[i + 1])) > 0)
		{
			count++;
			i += op_len - 1;
		}
		else if (!in_quotes && str[i] != ' ' && str[i] != '\t')
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t' || is_operator(str[i - 1], str[i]))
				count++;
		}
		i++;
	}
	if (in_quotes)
		return (-1);
	return (count);
}

static void	extract_tokens(const char *str, char **tokens,
		data_handle_args *data_args, t_list_head *n_head)
{
	char	quote_char;
	int		op_len;
	int		i, j, start, len;

	i = 0;
	j = 0;
	quote_char = 0;
	while (str[i] && j < data_args->count)
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
		else if ((op_len = is_operator(str[i], str[i + 1])) > 0)
		{
			len = op_len;
			i += op_len;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '"'
				&& str[i] != '\'' && !is_operator(str[i], str[i + 1]))
				i++;
			len = i - start;
		}
		if (len > 0)
		{
			tokens[j] = ft_malloc((len + 1) * sizeof(char), n_head);
			if (tokens[j])
				ft_strlcpy(tokens[j], str + start, len + 1);
			if (quote_char == '\'')
				data_args->expand_flags[j] = 0;
			else
				data_args->expand_flags[j] = 1;
			j++;
		}
		quote_char = 0;
	}
}

char	**split_string(const char *str, data_handle_args *data_args,
		t_list_head *n_head)
{
	char	**tokens;

	if (!str || !data_args)
		return (NULL);
	data_args->count = count_tokens(str);
	if (data_args->count == -1)
	{
		printf("Error: unclosed quote\n");
		return (NULL);
	}
	if (data_args->count == 0)
		return (NULL);
	data_args->expand_flags = ft_malloc(data_args->count * sizeof(char),
			n_head);
	if (!data_args->expand_flags)
		return (data_args->count = 0, NULL);
	tokens = ft_malloc((data_args->count + 1) * sizeof(char *), n_head);
	if (!tokens)
		return (data_args->count = 0, NULL);
	tokens[data_args->count] = NULL;
	extract_tokens(str, tokens, data_args, n_head);
	return (tokens);
}
