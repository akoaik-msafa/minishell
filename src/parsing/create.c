/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:37 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 19:26:37 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_cmd_args(token_t *current, token_t *end)
{
	int	count;

	count = 0;
	while (current < end && (current->type == t_word
			|| current->type == t_builtin || current->type == t_env_builtin))
	{
		count++;
		current++;
	}
	return (count);
}

static char	**create_cmd_args(token_t **current, token_t *end,
		struct list_head *head, t_data *data)
{
	char	**args;
	int		arg_count;
	int		i;

	arg_count = count_cmd_args(*current, end);
	args = ft_malloc((arg_count + 1) * sizeof(char *), head);
	if (!args)
		return (NULL);
	i = 0;
	while (i < arg_count)
	{
		if ((*current)->expand_flag == 1)
			args[i] = expand_variable((*current)->str, data);
		else
			args[i] = my_strdup((*current)->str, head);
		(*current)++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

tree_node	*create_cmd_node(token_t **current, token_t *end,
		t_list_head *n_head, t_data *data)
{
	tree_node	*node;
	char		**args;

	node = ft_malloc(sizeof(tree_node), n_head);
	if (!node)
		return (NULL);
	args = create_cmd_args(current, end, n_head, data);
	if (!args)
		return (NULL);
	node->type = cmd_node;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	node->redir_type = t_eof;
	node->heredoc_fd = -1;
	node->expand_flags = NULL;
	return (node);
}

tree_node	*create_pipe_node(tree_node *left, tree_node *right,
		t_list_head *n_head)
{
	tree_node	*node;

	node = ft_malloc(sizeof(tree_node), n_head);
	if (!node)
		return (NULL);
	node->type = pipe_node;
	node->args = NULL;
	node->left = left;
	node->right = right;
	node->filename = NULL;
	node->redir_type = t_eof;
	node->heredoc_fd = -1;
	node->expand_flags = NULL;
	return (node);
}

tree_node	*create_redir_node(token_t *redir_pos, tree_node *cmd, t_data *data)
{
	tree_node	*node;

	node = ft_malloc(sizeof(tree_node), data->n_head);
	if (!node)
		return (NULL);
	node->type = redir_node;
	node->args = NULL;
	node->left = cmd;
	node->right = NULL;
	node->filename = my_strdup((redir_pos + 1)->str, data->n_head);
	node->redir_type = redir_pos->type;
	node->heredoc_fd = -1;
	node->expand_flags = ft_malloc(2 * sizeof(char), data->n_head);
	if (node->expand_flags)
	{
		node->expand_flags[0] = (redir_pos + 1)->expand_flag;
		node->expand_flags[1] = '\0';
	}
	return (node);
}

/*
  create_cmd_args (line 15): Counts consecutive word 
  tokens using temp pointer,
	allocates memory
  for argument array, populates it with string pointers from tokens,
	and advances current pointer.

  create_cmd_node (line 44): Creates a command tree node by 
  calling create_cmd_args to get the
  args array,
	and initializing the node structure with type node_cmd 
	and null left/right pointers.

  parse_tokens (line 65): Main entry point that takes a token 
  array and count,
	validates input,
  and calls create_cmd_node to build a tree node from the tokens.

*/