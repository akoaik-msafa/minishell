/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/12 04:24:12 by akoaik           ###   ########.fr       */
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

static tree_node	*handle_pipe_parsing(token_t *tokens, token_t *pipe_pos,
		token_t *end, struct list_head *head)
{
	tree_node	*left;		// Pointer to store the parsed AST node for the left command (before pipe)
	tree_node	*right;		// Pointer to store the parsed AST node for the right command (after pipe)
	int			left_count;	// Integer count of how many tokens exist before the pipe operator
	int			right_count;	// Integer count of how many tokens exist after the pipe operator

	left_count = pipe_pos - tokens;			// Pointer arithmetic: subtract start address from pipe position to get token count before pipe
	right_count = end - pipe_pos - 1;		// Pointer arithmetic: subtract pipe position from end, minus 1 to exclude the pipe token itself
	left = parse_tokens(tokens, left_count, head);		// Recursively parse the left side tokens into an AST subtree
	right = parse_tokens(pipe_pos + 1, right_count, head);	// Recursively parse the right side tokens (skip pipe token with +1) into an AST subtree  
	if (!left || !right)				// Error checking: ensure both left and right parsing operations succeeded (not NULL)
		return (NULL);				// If either side failed to parse, return NULL to indicate parsing failure
	return (create_pipe_node(left, right, head));	// Success: create a new pipe node that connects left and right subtrees, return it
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
		return (handle_pipe_parsing(current, pipe_pos, end, head));
	else
		return (create_cmd_node(&current, end, head));
}
