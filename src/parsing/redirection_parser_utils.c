/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:15:49 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 19:24:10 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**merge_args(tree_node *left_node, tree_node *right_node,
		t_list_head *n_head)
{
	char	**new_args;
	int		i;
	int		j;
	int		left_cnt;
	int		right_cnt;

	i = 0;
	j = 0;
	left_cnt = 0;
	right_cnt = 0;
	while (left_node->args && left_node->args[left_cnt])
		left_cnt++;
	while (right_node->args && right_node->args[right_cnt])
		right_cnt++;
	new_args = ft_malloc((left_cnt + right_cnt + 1) * sizeof(char *), n_head);
	while (i < left_cnt)
	{
		new_args[i] = left_node->args[i];
		i++;
	}
	while (j < right_cnt)
		new_args[i++] = right_node->args[j++];
	new_args[i] = NULL;
	return (new_args);
}

tree_node	*handle_cmd_node_case(tree_node *left_node, tree_node *right_node,
		token_t *redir_pos, t_data *data)
{
	left_node->args = merge_args(left_node, right_node, data->n_head);
	return (create_redir_node(redir_pos, left_node, data));
}

tree_node	*handle_default_case(tree_node *left_node, tree_node *right_node,
		token_t *redir_pos, t_data *data)
{
	if (!left_node && right_node)
		return (create_redir_node(redir_pos, right_node, data));
	else
		return (create_redir_node(redir_pos, left_node, data));
}
