/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:32:17 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 23:30:53 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data_args(char *cmd_line, data_handle_args *data_args,
		t_list_head *n_head)
{
	data_args->count = count_tokens(cmd_line);
	if (data_args->count == -1)
	{
		printf("Error: unclosed quote\n");
		data_args->expand_flags = NULL;
		return ;
	}
	if (data_args->count == 0)
	{
		data_args->expand_flags = NULL;
		return ;
	}
	data_args->expand_flags = ft_malloc(data_args->count * sizeof(char),
			n_head);
	if (!data_args->expand_flags)
	{
		data_args->count = 0;
		return ;
	}
}


static int	process_token(char *cmd_line, data_handle_args *data_args,
		char **arguments, int j, t_data *data, int i)
{
	char	*word;
	int		end_pos;

	if (cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>')
	{
		data_args->start = i;
		if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') 
			|| (cmd_line[i] == '>' && cmd_line[i + 1] == '>'))
		{
			data_args->end_index = i + 2; // append or heredoc
			i++;
		}
		else
			data_args->end_index = i + 1;
		arguments[j] = alloc_tokens(cmd_line, data_args, data->n_head);
		data_args->expand_flags[j] = 0;
		return (data_args->end_index);
	}
	end_pos = extract_complete_word(cmd_line, i, &word, data);
	if (end_pos == -1)
		return (-1);
	arguments[j] = word;
	data_args->expand_flags[j] = data->current_expand_flag;
	return (end_pos);
}

char	**extract_tokens(char *cmd_line, data_handle_args *data_args,
		t_data *data)
{
	char	**arguments;
	int		i;
	int		j;

	arguments = ft_malloc((data_args->count + 1) * sizeof(char *), data->n_head);
	if (!arguments)
		return (NULL);
	arguments[data_args->count] = NULL;
	i = 0;
	j = 0;
	while (cmd_line[i] && j < data_args->count)
	{
		while (cmd_line[i] == ' ' || cmd_line[i] == '\t')
			i++;
		i = process_token(cmd_line, data_args, arguments, j, data, i);
		if (i == -1)
			break ;
		j++;
	}
	return (arguments);
}

char	**splite_token(char *cmd_line, data_handle_args *data_args,
		t_data *data)
{
	char **arguments;

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
