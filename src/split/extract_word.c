/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 15:25:01 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	calculate_word_length(char *cmd_line, int start)
{
	char	quote_flag;
	int		i;
	int		total_len;
	int		end_quote;
	int		j;

	i = start;
	total_len = 0;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t'
		&& cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			quote_flag = cmd_line[i];
			end_quote = find_closed_quote(cmd_line, i, &quote_flag);
			if (end_quote == -1)
				return (-1);
			j = i + 1;
			while (j < end_quote)
			{
				if (quote_flag == '\'' && cmd_line[j] == '$')
					total_len += 2;
				else
					total_len++;
				j++;
			}
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

static int	copy_word_content(char *cmd_line, int start, char *word)
{
	char	quote_flag;
	int		i;
	int		result_pos;
	int		end_quote;

	i = start;
	result_pos = 0;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t'
		&& cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			quote_flag = cmd_line[i];
			end_quote = find_closed_quote(cmd_line, i, &quote_flag);
			i++;
			while (i < end_quote)
			{
				if (quote_flag == '\'' && cmd_line[i] == '$')
				{
					word[result_pos++] = '\\';
					word[result_pos++] = '$';
					i++;
				}
				else
					word[result_pos++] = cmd_line[i++];
			}
			i++;
		}
		else
			word[result_pos++] = cmd_line[i++];
	}
	word[result_pos] = '\0';
	return (i);
}

int	extract_complete_word(char *cmd_line, data_handle_args *data_args,
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
