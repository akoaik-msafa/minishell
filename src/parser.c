/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/11 23:33:26 by akoaik           ###   ########.fr       */
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
	token_t		*current;
	token_t		*end;
	token_t		*pipe_pos;
	tree_node	*left;
	tree_node	*right;
	int			left_count;
	int			right_count;

	if (!tokens || count == 0)
		return (NULL);
	current = tokens;
	end = tokens + count;
	pipe_pos = find_pipe(current, end);
	if (pipe_pos)
	{
		left_count = pipe_pos - current;
		right_count = end - pipe_pos - 1;
		left = parse_tokens(current, left_count, head);
		right = parse_tokens(pipe_pos + 1, right_count, head);
		if (!left || !right)
			return (NULL);
		return (create_pipe_node(left, right, head));
	}
	else
	{
		return (create_cmd_node(&current, end, head));
	}
}
