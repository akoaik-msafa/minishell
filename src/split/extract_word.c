/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/25 22:00:00 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	calculate_word_length(char *cmd_line, int start)
{
	int		i, total_len;
	char	quote_flag;
	data_handle_args temp_data;

	i = start;
	total_len = 0;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t' 
		&& cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			temp_data.start = i;
			find_closed_quote(cmd_line, &quote_flag, &temp_data);
			if (temp_data.end_index == -1)
				return (-1);
			total_len += temp_data.end_index - temp_data.start - 1;
			i = temp_data.end_index + 1;
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
	int		i, result_pos;
	char	quote_flag;
	data_handle_args temp_data;

	i = start;
	result_pos = 0;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t' 
		&& cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			temp_data.start = i;
			find_closed_quote(cmd_line, &quote_flag, &temp_data);
			i++;
			while (i < temp_data.end_index)
				word[result_pos++] = cmd_line[i++];
			i++;
		}
		else
			word[result_pos++] = cmd_line[i++];
	}
	word[result_pos] = '\0';
	return (i);
}

int	extract_complete_word(char *cmd_line, int start, char **result, t_list_head *n_head)
{
	int		total_len, end_pos;
	char	*word;

	total_len = calculate_word_length(cmd_line, start);
	if (total_len == -1)
		return (-1);
	word = ft_malloc((total_len + 1) * sizeof(char), n_head);
	if (!word)
		return (-1);
	end_pos = copy_word_content(cmd_line, start, word);
	*result = word;
	return (end_pos);
}