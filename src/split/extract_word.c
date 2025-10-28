/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 23:18:16 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	calculate_word_length(char *cmd_line, int start)
{
	char	f_quote;
	int		i;
	int		total_len;
	int		end_quote;

	i = start;
	total_len = 0;
	while (cmd_line[i] && !is_word_delimiter(cmd_line[i]))
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			f_quote = cmd_line[i];
			end_quote = find_closed_quote(cmd_line, i, &f_quote);
			if (end_quote == -1)
				return (-1);
			total_len += count_quoted_length(cmd_line, i, f_quote, end_quote);
			i = end_quote + 1;
		}
		else
		{
			total_len++;
			i++;
		}
	}
	return (total_len);
}

static int	copy_quoted_content(char *cmd_line, char *word, int *i,
		int *result_pos)
{
	char	quote_flag;
	int		end_quote;

	quote_flag = cmd_line[*i];
	end_quote = find_closed_quote(cmd_line, *i, &quote_flag);
	(*i)++;
	while (*i < end_quote)
	{
		if (quote_flag == '\'' && cmd_line[*i] == '$')
		{
			word[(*result_pos)++] = '\\';
			word[(*result_pos)++] = '$';
			(*i)++;
		}
		else
			word[(*result_pos)++] = cmd_line[(*i)++];
	}
	(*i)++;
	return (0);
}

static int	copy_word_content(char *cmd_line, int start, char *word)
{
	int		i;
	int		result_pos;

	i = start;
	result_pos = 0;
	while (cmd_line[i] && !is_word_delimiter(cmd_line[i]))
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
			copy_quoted_content(cmd_line, word, &i, &result_pos);
		else
			word[result_pos++] = cmd_line[i++];
	}
	word[result_pos] = '\0';
	return (i);
}

int	extract_complete_word(char *cmd_line, t_data_handle_args *data_args,
		char **result, t_data *data)
{
	int		total_len;
	int		end_pos;
	char	*word;

	total_len = calculate_word_length(cmd_line, data_args->start);
	if (total_len == -1)
		return (-1);
	word = ft_malloc((total_len + 1) * sizeof(char), data->n_head);
	if (!word)
		return (-1);
	if (data_args->is_delimiter)
	{
		if (cmd_line[data_args->start] == '\''
			|| cmd_line[data_args->start] == '"')
			data->current_expand_flag = 0;
		else
			data->current_expand_flag = 1;
	}
	else if (cmd_line[data_args->start] == '\'')
		data->current_expand_flag = 0;
	else
		data->current_expand_flag = 1;
	end_pos = copy_word_content(cmd_line, data_args->start, word);
	*result = word;
	return (end_pos);
}
