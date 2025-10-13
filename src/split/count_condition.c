/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:23:42 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/13 14:32:05 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_opening_quote(char c, t_token_state *state)
{
	if (!state->in_quotes && (c == '"' || c == '\''))
		return (1);
	return (0);
}

int	is_closing_quote(char c, t_token_state *state)
{
	if (state->in_quotes && c == state->quote_char)
		return (1);
	return (0);
}

int	is_operator_char(const char *str, int i, t_token_state *state)
{
	if (!state->in_quotes && is_operator(str[i], str[i + 1]) > 0)
		return (1);
	return (0);
}

int	is_whitespace_char(char c, t_token_state *state)
{
	if (!state->in_quotes && is_whitespace(c))
		return (1);
	return (0);
}

int	is_regular_char(char c, t_token_state *state)
{
	if (!state->in_quotes && !is_whitespace(c))
		return (1);
	return (0);
}
