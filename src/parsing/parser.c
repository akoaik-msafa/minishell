/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 19:32:35 by akoaik           ###   ########.fr       */
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

static int	validate_syntax(token_t *current, token_t *end, token_t *pipe_pos,
		token_t *redir_pos)
{
	if (pipe_pos)
	{
		if (pipe_pos == current || pipe_pos == end - 1)
		{
			printf("syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	if (redir_pos)
	{
		if (redir_pos + 1 >= end || (redir_pos + 1)->type != t_word)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (0);
		}
	}
	return (1);
}

static int	init_parse_positions(token_t *tokens, int count, token_t **pipe_pos,
		token_t **redir_pos)
{
	token_t	*current;
	token_t	*end;

	if (!tokens || count == 0)
		return (0);
	current = tokens;
	end = tokens + count;
	*pipe_pos = find_pipe(current, end);
	*redir_pos = find_redirection(current, end);
	if (!validate_syntax(current, end, *pipe_pos, *redir_pos))
		return (0);
	return (1);
}

static tree_node	*handle_pipe_parsing(data_handle_args *args,
		t_list_head *n_head, t_data *data)
{
	tree_node	*left;
	tree_node	*right;
	int			left_count;
	int			right_count;

	left_count = args->pipe_position - args->tokens;
	right_count = args->end - args->pipe_position - 1;
	left = parse_tokens(args->tokens, left_count, n_head, data);
	right = parse_tokens(args->pipe_position + 1, right_count, n_head, data);
	if (!left || !right)
		return (NULL);
	return (create_pipe_node(left, right, n_head));
}

tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head,
		t_data *data)
{
	token_t				*pipe_position;
	token_t				*redir_position;
	data_handle_args	args;

	if (!init_parse_positions(tokens, count, &pipe_position, &redir_position))
		return (NULL);
	if (pipe_position)
	{
		args = (data_handle_args){tokens, pipe_position, tokens + count, 0, 0,
			0, NULL, NULL, 0};
		return (handle_pipe_parsing(&args, n_head, data));
	}
	if (redir_position)
		return (new_handle_redirection_parsing(tokens, redir_position,
				tokens + count, data));
	return (create_cmd_node(&tokens, tokens + count, n_head, data));
}

/*
  find_pipe (line 15): Iterates through token array from 
  start to end,
	returns pointer to first pipe token found, or NULL if 
	none exists.

  handle_pipe_parsing (line 29): Splits tokens at pipe 
  position into left and right parts,
	recursively calls parse_tokens on each side,
		creates pipe node connecting the results.

  parse_tokens (line 46): Main parsing entry point that 
  validates input,
	searches for pipes,
	and either delegates to handle_pipe_parsing or creates command 
	node directly.
*/
