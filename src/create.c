/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:37 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/11 19:14:37 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**create_cmd_args(token_t **current, token_t *end,
		struct list_head *head, t_env *env)
{
	char	**args;
	token_t	*temp;
	int		arg_count;
	int		i;

	temp = *current;
	arg_count = 0;
	while (temp < end && temp->type == t_word)
	{
		arg_count++;
		temp++;
	}
	args = ft_malloc((arg_count + 1) * sizeof(char *), head);
	if (!args)
		return (NULL);
	i = 0;
	while (i < arg_count)
	{
		args[i] = expand_variable((*current)->str, env, head);
		(*current)++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

tree_node	*create_cmd_node(token_t **current, token_t *end,
		struct list_head *head, t_env *env)
{
	tree_node	*node;
	char		**args;

	node = ft_malloc(sizeof(tree_node), head);
	if (!node)
		return (NULL);
	args = create_cmd_args(current, end, head, env);
	if (!args)
		return (NULL);
	node->type = node_cmd;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	node->redir_type = t_eof;
	
	if (*current < end && ((*current)->type == t_re_out || 
		(*current)->type == t_re_in || (*current)->type == t_re_append || 
		(*current)->type == t_re_heredoc))
	{
		node->redir_type = (*current)->type;
		(*current)++;
		if (*current < end && (*current)->type == t_word)
		{
			node->filename = (*current)->str;
			(*current)++;
		}
	}
	return (node);
}

tree_node	*create_pipe_node(tree_node *left, tree_node *right,
		struct list_head *head)
{
	tree_node	*node;

	node = ft_malloc(sizeof(tree_node), head);
	if (!node)
		return (NULL);
	node->type = node_pipe;
	node->args = NULL;
	node->left = left;
	node->right = right;
	node->filename = NULL;
	node->redir_type = t_eof;
	return (node);
}

/*
  create_cmd_args (line 15): Counts consecutive word tokens using temp pointer,
	allocates memory
  for argument array, populates it with string pointers from tokens,
	and advances current pointer.

  create_cmd_node (line 44): Creates a command tree node by calling create_cmd_args to get the
  args array,
	and initializing the node structure with type node_cmd and null left/right pointers.

  parse_tokens (line 65): Main entry point that takes a token array and count,
	validates input,
  and calls create_cmd_node to build a tree node from the tokens.

*/