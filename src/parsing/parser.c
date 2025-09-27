/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/26 21:14:24 by akoaik           ###   ########.fr       */
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

static token_t	*find_redirection(token_t *current, token_t *end)
{
	token_t	*start;

	start = current;
	while (start < end)
	{
		if (start->type == t_re_heredoc || start->type == t_re_in ||
			start->type == t_re_out || start->type == t_re_append)
			return (start);
		start++;
	}
	return (NULL);
}

static tree_node	*handle_pipe_parsing(data_handle_args *args, t_list_head *n_head, t_env *env)
{
	tree_node	*left;
	tree_node	*right;
	int			left_count;
	int			right_count;

	left_count = args->pipe_position - args->tokens;
	right_count = args->end - args->pipe_position - 1;
	left = parse_tokens(args->tokens, left_count, n_head, env);
	right = parse_tokens(args->pipe_position + 1, right_count, n_head, env);
	if (!left || !right)
		return (NULL);
	return (create_pipe_node(left, right, n_head));
}

/*static tree_node	*handle_redirection_parsing(token_t *tokens, token_t *redir_pos, token_t *end, t_list_head *n_head, t_env *env)
{
	tree_node	*cmd_node;
	tree_node	*redir_node;
	int			cmd_count;
	char		*filename;

	printf("2\n");
	cmd_count = redir_pos - tokens;
	if (cmd_count > 0)
		cmd_node = parse_tokens(tokens, cmd_count, n_head, env);
	else
		cmd_node = NULL;

	if (redir_pos + 1 < end && (redir_pos + 1)->type == t_word)
		filename = (redir_pos + 1)->str;
	else
		return (NULL);

	redir_node = create_redir_node(redir_pos->type, filename, cmd_node, n_head);
	return (redir_node);
}*/

void print_tree(tree_node *node, int depth)
{
	int i;

	if (!node)
		return;

	for (i = 0; i < depth; i++)
		printf("  ");

	if (node->type == cmd_node)
	{
		printf("CMD_NODE: ");
		if (node->args && node->args[0])
			printf("%s\n", node->args[0]);
		else
			printf("(empty)\n");
	}
	else if (node->type == pipe_node)
	{
		printf("PIPE_NODE\n");
		if (node->left)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("left:\n");
			print_tree(node->left, depth + 2);
		}
		if (node->right)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("right:\n");
			print_tree(node->right, depth + 2);
		}
	}
	else if (node->type == redir_node)
	{
		printf("REDIR_NODE: ");
		if (node->redir_type == t_re_heredoc)
			printf("<<");
		else if (node->redir_type == t_re_out)
			printf(">");
		else if (node->redir_type == t_re_append)
			printf(">>");
		else if (node->redir_type == t_re_in)
			printf("<");

		if (node->filename)
			printf(" %s\n", node->filename);
		else
			printf(" (no file)\n");

		if (node->left)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("left:\n");
			print_tree(node->left, depth + 2);
		}
	}
}

tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head, t_env *env)
{
	token_t	*current;
	token_t	*end;
	token_t	*pipe_position;
	token_t	*redir_position;
    data_handle_args args;

	if (!tokens || count == 0)
		return (NULL);
	current = tokens;
	end = tokens + count;
	pipe_position = find_pipe(current, end);
	if (pipe_position)
	{
		args = (data_handle_args){current, pipe_position, end, 0, 0, 0, NULL};
		return (handle_pipe_parsing(&args, n_head, env));
	}
	redir_position = find_redirection(current, end);
	if (redir_position)
	{
		printf("=== TESTING NEW REDIRECTION PARSER ===\n");
		return (new_handle_redirection_parsing(current, redir_position, end, n_head, env));
	}
	else
		return (create_cmd_node(&current, end, n_head, env));
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
