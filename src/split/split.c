/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:32:17 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 20:31:12 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data_args(char *cmd_line, t_data_handle_args *data_args,
		t_list_head *n_head)
{
	data_args->count = count_refactored(cmd_line);
	if (data_args->count == -1)
	{
		printf("Error: unclosed quote\n");
		data_args->expansion = NULL;
		data_args->delimiter = NULL;
		return ;
	}
	if (data_args->count == 0)
	{
		data_args->expansion = NULL;
		data_args->delimiter = NULL;
		return ;
	}
	data_args->expansion = ft_malloc(data_args->count * sizeof(char), n_head);
	data_args->delimiter = ft_malloc(data_args->count * sizeof(char), n_head);
	if (!data_args->expansion || !data_args->delimiter)
	{
		data_args->count = 0;
		return ;
	}
}

static void	init_operator_token(char *cmd_line, t_data_handle_args *data_args,
		int i)
{
	if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		|| (cmd_line[i] == '>' && cmd_line[i + 1] == '>'))
	{
		data_args->end_index = i + 2;
		if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
			data_args->is_delimiter = 1;
	}
	else
		data_args->end_index = i + 1;
}

static int	find_token_end(char *cmd_line, t_data_handle_args *data_args,
		char **arguments, t_data *data)
{
	char	*word;
	int		end_pos;
	int		i;

	i = data_args->start;
	if (cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>')
	{
		init_operator_token(cmd_line, data_args, i);
		arguments[data_args->token_index] = alloc_tokens(cmd_line, data_args,
				data->n_head);
		data_args->expansion[data_args->token_index] = 0;
		data_args->delimiter[data_args->token_index] = 0;
		return (data_args->end_index);
	}
	data_args->start = i;
	end_pos = extract_complete_word(cmd_line, data_args, &word, data);
	if (end_pos == -1)
		return (-1);
	arguments[data_args->token_index] = word;
	data_args->expansion[data_args->token_index] = data->current_expand_flag;
	data_args->delimiter[data_args->token_index] = data_args->is_delimiter;
	data_args->is_delimiter = 0;
	return (end_pos);
}

char	**extract_tokens(char *cmd_line, t_data_handle_args *data_args,
		t_data *data)
{
	char	**arguments;
	int		pos;

	arguments = ft_malloc((data_args->count + 1) * sizeof(char *),
			data->n_head);
	if (!arguments)
		return (NULL);
	arguments[data_args->count] = NULL;
	pos = 0;
	data_args->token_index = 0;
	data_args->is_delimiter = 0;
	while (cmd_line[pos] && data_args->token_index < data_args->count)
	{
		while (cmd_line[pos] == ' ' || cmd_line[pos] == '\t')
			pos++;
		data_args->start = pos;
		pos = find_token_end(cmd_line, data_args, arguments, data);
		if (pos == -1)
			break ;
		data_args->token_index++;
	}
	return (arguments);
}

char	**splite_token(char *cmd_line, t_data_handle_args *data_args,
		t_data *data)
{
	char	**arguments;

	if (!cmd_line)
		return (NULL);
	init_data_args(cmd_line, data_args, data->n_head);
	if (data_args->count == -1)
		return (NULL);
	arguments = extract_tokens(cmd_line, data_args, data);
	if (!arguments)
	{
		data_args->count = 0;
		return (NULL);
	}
	return (arguments);
}
