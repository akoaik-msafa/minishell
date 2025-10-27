/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:37 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 01:13:42 by msafa            ###   ########.fr       */
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
		if (has_unescaped_dollar((*current)->str))
		{
			args[i] = expand_variable((*current)->str, data);
			args[i] = my_ft_strtrim(args[i], " \t", head);
		}
		else
			args[i] = remove_escape_dollar((*current)->str, data);
		(*current)++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_tree_node	*create_cmd_node(token_t **current, token_t *end,
		t_list_head *n_head, t_data *data)
{
	t_tree_node	*node;
	char		**args;

	node = ft_malloc(sizeof(t_tree_node), n_head);
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
	node->expansion = NULL;
	return (node);
}

t_tree_node	*create_pipe_node(t_tree_node *left, t_tree_node *right,
		t_list_head *n_head)
{
	t_tree_node	*node;

	node = ft_malloc(sizeof(t_tree_node), n_head);
	if (!node)
		return (NULL);
	node->type = pipe_node;
	node->args = NULL;
	node->left = left;
	node->right = right;
	node->filename = NULL;
	node->redir_type = t_eof;
	node->heredoc_fd = -1;
	node->expansion = NULL;
	return (node);
}

t_tree_node	*create_redir_node(token_t *redir_pos, t_tree_node *cmd,
		t_data *data)
{
	t_tree_node	*node;

	node = ft_malloc(sizeof(t_tree_node), data->n_head);
	if (!node)
		return (NULL);
	node->type = redir_node;
	node->args = NULL;
	node->left = cmd;
	node->right = NULL;
	node->filename = my_strdup((redir_pos + 1)->str, data->n_head);
	node->redir_type = redir_pos->type;
	node->heredoc_fd = -1;
	node->expansion = ft_malloc(2 * sizeof(char), data->n_head);
	if (node->expansion)
	{
		node->expansion[0] = (redir_pos + 1)->expand_flag;
		node->expansion[1] = '\0';
	}
	return (node);
}
