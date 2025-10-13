/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_refactored.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:44:40 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 14:27:25 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_operator(char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
		return (2);
	if (c1 == '>' && c2 == '>')
		return (2);
	if (c1 == '|' || c1 == '<' || c1 == '>')
		return (1);
	return (0);
}

int	process_string(const char *str, int *count)
{
	int				i;
	t_token_state	state;

	i = 0;
	state.in_quotes = 0;
	state.in_word = 0;
	while (str[i])
	{
		if (is_opening_quote(str[i], &state))
			handle_quote_start(count, &state, str[i]);
		else if (is_closing_quote(str[i], &state))
			state.in_quotes = 0;
		else if (is_operator_char(str, i, &state))
			handle_operator(str, &i, count, &state);
		else if (is_whitespace_char(str[i], &state))
			handle_whitespace(&state);
		else if (is_regular_char(str[i], &state))
			handle_regular_char(count, &state);
		i++;
	}
	return (state.in_quotes);
}

int	count_refactored(const char *str)
{
	int	count;

	count = 0;
	if (process_string(str, &count))
		return (-1);
	return (count);
}
