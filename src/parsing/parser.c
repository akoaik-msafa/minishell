/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 01:13:46 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_token	*find_pipe(t_token *current, t_token *end)
{
	t_token	*start;

	start = current;
	while (start < end)
	{
		if (start->type == t_pipe)
			return (start);
		start++;
	}
	return (NULL);
}

static int	validate_syntax(t_token *current, t_token *end, t_token *pipe_pos,
		t_token *redir_pos)
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

static int	init_parse_positions(t_token *tokens, int count, t_token **pipe_pos,
		t_token **redir_pos)
{
	t_token	*current;
	t_token	*end;

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

static t_tree_node	*handle_pipe_parsing(t_data_handle_args *args,
		t_list_head *n_head, t_data *data)
{
	t_tree_node	*left;
	t_tree_node	*right;
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

t_tree_node	*parse_tokens(t_token *tokens, int count, t_list_head *n_head,
		t_data *data)
{
	t_token				*pipe_position;
	t_token				*redir_position;
	t_data_handle_args	args;

	if (!init_parse_positions(tokens, count, &pipe_position, &redir_position))
		return (NULL);
	if (pipe_position)
	{
		args = (t_data_handle_args){tokens, pipe_position, tokens + count, 0, 0,
			0, NULL, NULL, 0, 0};
		return (handle_pipe_parsing(&args, n_head, data));
	}
	if (redir_position)
		return (handle_redirection_parsing(tokens, redir_position,
				tokens + count, data));
	return (create_cmd_node(&tokens, tokens + count, n_head, data));
}
