/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:37 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/10 16:05:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_cmd_args(token_t *current, token_t *end)
{
	int	arg_count;

	arg_count = 0;
	while (current < end && current->type == t_word)
	{
		arg_count++;
		current++;
	}
	return (arg_count);
}

static char	**populate_cmd_args(token_t **current, int arg_count,
		struct list_head *head)
{
	char	**args;
	int		i;

	args = ft_malloc((arg_count + 1) * sizeof(char *), head);
	if (!args)
		return (NULL);
	i = 0;
	while (i < arg_count)
	{
		args[i] = (*current)->str;
		(*current)++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static tree_node	*create_cmd_node(token_t **current, token_t *end,
		struct list_head *head)
{
	tree_node	*node;
	char		**args;
	int			arg_count;

	node = ft_malloc(sizeof(tree_node), head);
	if (!node)
		return (NULL);
	arg_count = count_cmd_args(*current, end);
	args = populate_cmd_args(current, arg_count, head);
	if (!args)
		return (NULL);
	node->type = node_cmd;
	node->args = args;
	node->left = NULL;
	node->rigt = NULL;
	node->filename = NULL;
	node->redir_type = t_eof;
	return (node);
}

tree_node	*parse_tokens(token_t *tokens, int count, struct list_head *head)
{
	token_t *current;
	token_t *end;

	if (!tokens || count == 0)
		return (NULL);
	current = tokens;
	end = tokens + count;
	return (create_cmd_node(&current, end, head));
}