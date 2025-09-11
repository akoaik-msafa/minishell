/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/11 19:44:38 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static token_t	*find_pipe(token_t *start, token_t *end)
{
	token_t	*current;

	current = start;
	while (current < end)
	{
		if (current->type == t_pipe)
			return (current);
		current++;
	}
	return (NULL);
}

tree_node	*parse_tokens(token_t *tokens, int count, struct list_head *head)
{
	token_t	*current;
	token_t	*end;
	token_t	*pipe_pos;

	if (!tokens || count == 0)
		return (NULL);
	current = tokens;
	end = tokens + count;
	pipe_pos = find_pipe(current, end);
	if (pipe_pos)
	{
		// TODO: Create pipe node with left and right children
		return (NULL);
	}
	else
	{
		// No pipe found, create simple command node
		return (create_cmd_node(&current, end, head));
	}
}