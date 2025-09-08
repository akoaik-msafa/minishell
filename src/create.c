/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:35:08 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/08 20:09:20 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

tree_node *creat_node(node_type type, struct list_head *hn)
{
	tree_node *node = ft_malloc(sizeof(tree_node), &(hn->head));
	if (!node)
		return (NULL);
	node->type = type ;
	node->args = NULL ;
	node->left = NULL ;
	node->rigt = NULL ;
	node->filename = NULL ;
	node->redir_type = t_eof ;
	return (node);
}


