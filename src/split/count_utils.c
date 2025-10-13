/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:24:06 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 14:32:09 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

void	handle_quote_start(int *count, t_token_state *state, char c)
{
	if (!state->in_word)
	{
		(*count)++;
		state->in_word = 1;
	}
	state->quote_char = c;
	state->in_quotes = 1;
}

void	handle_operator(const char *str, int *i, int *count,
		t_token_state *state)
{
	int	op_len;

	state->in_word = 0;
	(*count)++;
	op_len = is_operator(str[*i], str[*i + 1]);
	*i += op_len - 1;
}

void	handle_whitespace(t_token_state *state)
{
	state->in_word = 0;
}

void	handle_regular_char(int *count, t_token_state *state)
{
	if (!state->in_word)
	{
		(*count)++;
		state->in_word = 1;
	}
}
