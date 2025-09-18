/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 05:45:59 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static token_t	*find_pipe(token_t *current, token_t *end)
{
	token_t	*start;

	start = current;
	while (start < end)
	{
		if (start->type == t_pipe)
			return (start);
		start++;
	}
	return (NULL);
}

static tree_node	*handle_pipe_parsing(token_t *tokens,
		token_t *pipe_position, token_t *end, t_list_head *n_head)
{
	tree_node	*left;
	tree_node	*right;
	int			left_count;
	int			right_count;

	left_count = pipe_position - tokens;
	right_count = end - pipe_position - 1;
	left = parse_tokens(tokens, left_count, n_head);
	right = parse_tokens(pipe_position + 1, right_count, n_head);
	if (!left || !right)
		return (NULL);
	return (create_pipe_node(left, right, n_head));
}

tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head)
{
	token_t	*current;
	token_t	*end;
	token_t	*pipe_position;

	if (!tokens || count == 0)
		return (NULL);
	current = tokens;
	end = tokens + count;
	pipe_position = find_pipe(current, end);
	if (pipe_position)
		return (handle_pipe_parsing(current, pipe_position, end, n_head));
	else
		return (create_cmd_node(&current, end, n_head));
}
/*
  find_pipe (line 15): Iterates through token array from start to end,
	returns pointer to first pipe token found, or NULL if none exists.

  handle_pipe_parsing (line 29): Splits tokens at pipe position into left and right parts,
	recursively calls parse_tokens on each side,
		creates pipe node connecting the results.

  parse_tokens (line 46): Main parsing entry point that validates input,
	searches for pipes,
	and either delegates to handle_pipe_parsing or creates command node directly.

*/
