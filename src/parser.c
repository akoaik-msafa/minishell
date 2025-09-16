/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/12 22:36:39 by akoaik           ###   ########.fr       */
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
		token_t *end, struct list_head *head, t_env *env)
{
	tree_node	*left;
	tree_node	*right;
	int			left_count;
	int			right_count;

	left_count = pipe_pos - tokens;
	right_count = end - pipe_pos - 1;
	left = parse_tokens(tokens, left_count, head, env);
	right = parse_tokens(pipe_pos + 1, right_count, head, env);
	if (!left || !right)
		return (NULL);
	return (create_pipe_node(left, right, head));
}

tree_node	*parse_tokens(token_t *tokens, int count, struct list_head *head, t_env *env)
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
		return (handle_pipe_parsing(current, pipe_pos, end, head, env));
	else
		return (create_cmd_node(&current, end, head, env));
}

/*
  find_pipe (line 15): Iterates through token array from start to end,
	returns pointer to first pipe token found, or NULL if none exists.

  handle_pipe_parsing (line 29): Splits tokens at pipe position into left and right parts,
	recursively calls parse_tokens on each side, creates pipe node connecting the results.

  parse_tokens (line 46): Main parsing entry point that validates input, searches for pipes,
	and either delegates to handle_pipe_parsing or creates command node directly.

*/
