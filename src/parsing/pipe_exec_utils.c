/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:04:36 by msafa             #+#    #+#             */
/*   Updated: 2025/10/27 23:05:08 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_expand_flag(t_tree_node *node)
{
	if (node->expansion)
		return (node->expansion[0]);
	return (1);
}

int	process_heredoc_node(t_tree_node *node, t_data *data)
{
	int	expand_flag;

	if (node->heredoc_fd == -1)
	{
		expand_flag = get_expand_flag(node);
		node->heredoc_fd = here_doc(node->filename, data, expand_flag);
		if (node->heredoc_fd == -1)
			return (-1);
	}
	return (collect_heredocs(node->left, data));
}

int	process_pipe_node(t_tree_node *node, t_data *data)
{
	if (collect_heredocs(node->left, data) == -1)
		return (-1);
	return (collect_heredocs(node->right, data));
}
