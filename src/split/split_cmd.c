/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:53:09 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 13:29:56 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	data_init(t_data_handle_args *data_args)
{
	data_args->count = 0;
	data_args->expansion = NULL;
}

int	count_token_array(t_token *tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count].type != t_eof)
		count++;
	return (count);
}

t_token	*tokenize_input(char *cmd_line, t_data *data)
{
	t_token				*tokens_arr;
	char				**arguments;
	t_data_handle_args	data_args;

	data_init(&data_args);
	arguments = splite_token(cmd_line, &data_args, data);
	if (!arguments)
		return (NULL);
	tokens_arr = ft_malloc((data_args.count + 1) * sizeof(t_token),
			data->n_head);
	if (!tokens_arr)
		return (NULL);
	fill_tokens_array(tokens_arr, arguments, &data_args);
	return (tokens_arr);
}
