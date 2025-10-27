/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:11:30 by msafa             #+#    #+#             */
/*   Updated: 2025/10/27 23:12:04 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_quoted_length(char *cmd_line, int i, char quote_flag,
		int end_quote)
{
	int	j;
	int	len;

	j = i + 1;
	len = 0;
	while (j < end_quote)
	{
		if (quote_flag == '\'' && cmd_line[j] == '$')
			len += 2;
		else
			len++;
		j++;
	}
	return (len);
}

int	is_word_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}
