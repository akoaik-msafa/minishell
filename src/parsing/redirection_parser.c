/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:14:12 by msafa             #+#    #+#             */
/*   Updated: 2025/10/22 18:43:12 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

token_t	*find_redirection(token_t *current, token_t *end)
{
	token_t	*start;

	start = current;
	while (start < end)
	{
		if (start->type == t_re_heredoc || start->type == t_re_in
			|| start->type == t_re_out || start->type == t_re_append)
			return (start);
		start++;
	}
	return (NULL);
}

static tree_node	*parse_left_side(token_t *tokens, token_t *redir_pos,
		t_list_head *n_head, t_data *data)
{
	int	cmd_count;

	cmd_count = redir_pos - tokens;
	if (cmd_count > 0)
	{
		return (parse_tokens(tokens, cmd_count, n_head, data));
	}
	return (NULL);
}

static tree_node	*parse_right_side(token_t *redir_pos, token_t *end,
		t_list_head *n_head, t_data *data)
{
	int		remaining_count;
	token_t	*remaining_start;

	remaining_start = redir_pos + 2;
	remaining_count = end - remaining_start;
	if (remaining_count > 0)
	{
		return (parse_tokens(remaining_start, remaining_count, n_head, data));
	}
	return (NULL);
}

static tree_node	*handle_redir_node_case(tree_node *left_node,
		tree_node *right_node, token_t *redir_pos, t_data *data)
{
	tree_node	*temp_rihgt_node;

	temp_rihgt_node = right_node;
	while (temp_rihgt_node->left && temp_rihgt_node->left->type == redir_node)
		temp_rihgt_node = temp_rihgt_node->left;
	if (!temp_rihgt_node->left)
		temp_rihgt_node->left = left_node;
	return (create_redir_node(redir_pos, right_node, data));
}

tree_node	*handle_redirection_parsing(token_t *tokens, token_t *redir_pos,
		token_t *end, t_data *data)
{
	tree_node	*left_node;
	tree_node	*right_node;

	if (redir_pos + 1 >= end || (redir_pos + 1)->type != t_word)
		return (NULL);
	left_node = parse_left_side(tokens, redir_pos, data->n_head, data);
	right_node = parse_right_side(redir_pos, end, data->n_head, data);
	if (right_node && right_node->type == redir_node)
		return (handle_redir_node_case(left_node, right_node, redir_pos, data));
	else if (right_node && right_node->type == cmd_node && left_node
		&& left_node->type == cmd_node)
		return (handle_cmd_node_case(left_node, right_node, redir_pos, data));
	else
		return (handle_default_case(left_node, right_node, redir_pos, data));
}

/* SIMPLIFIED VERSION - COMPARE WITH ABOVE */

tree_node	*handle_redirection_parsing_v2(token_t *tokens, token_t *redir_pos,
		token_t *end, t_data *data)
{
	tree_node	*left_node;
	tree_node	*right_node;
	int			left_count;
	int			right_count;

	// Validate: redirection must have a filename after it (e.g., "< file")
	if (redir_pos + 1 >= end || (redir_pos + 1)->type != t_word)
		return (NULL);

	// Parse LEFT side: tokens BEFORE the redirection (e.g., "echo hello > file")
	// left_count = number of tokens before redirection
	left_count = redir_pos - tokens;
	if (left_count > 0)
		left_node = parse_tokens(tokens, left_count, data->n_head, data);
	else
		left_node = NULL;

	// Parse RIGHT side: tokens AFTER the redirection filename (e.g., "< file cat")
	// Skip 2 positions: redirection operator + filename
	right_count = end - (redir_pos + 2);
	if (right_count > 0)
		right_node = parse_tokens(redir_pos + 2, right_count, data->n_head, data);
	else
		right_node = NULL;

	// CASE 1: Right side is another redirection (e.g., "< file1 > file2")
	// Chain redirections together with left_node at the deepest level
	if (right_node && right_node->type == redir_node)
		return (handle_redir_node_case(left_node, right_node, redir_pos, data));

	// CASE 2: Both sides are commands (e.g., "echo hello > file cat")
	// Merge the command arguments from both sides
	if (right_node && right_node->type == cmd_node && left_node
		&& left_node->type == cmd_node)
		return (handle_cmd_node_case(left_node, right_node, redir_pos, data));

	// CASE 3: Default case - simple redirection
	// Prefer right_node if exists, otherwise use left_node
	// Examples: "> file", "echo > file", "< file cat"
	if (right_node)
		return (create_redir_node(redir_pos, right_node, data));
	return (create_redir_node(redir_pos, left_node, data));
}

