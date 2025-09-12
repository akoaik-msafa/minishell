/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 03:27:21 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/12 21:19:32 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

struct tree* createNode(int value) {
    struct tree* new_node = malloc(sizeof(struct tree));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct tree *insert (struct tree *root, int value)
{
	if (root == NULL)
		return createNode(value) ;
	
	if (value < root->value)
	{
		root->left = insert(root->left, value);
	}
	else if (value > root->value)
	{
		root->right = insert(root->right, value);
	}
	return (root) ;
}

void in_order(struct tree *node)
{
	if (node == NULL)
		return ;
	in_order(node->left);
	printf("%d", node->value);
	in_order(node->right);
}

int main (void) 
{
	struct tree *root = NULL ;
	
	root = insert(root , 4);
	insert(root, 2);
	insert(root, 1);
	insert(root, 3);
	insert(root, 7);
	insert(root, 6);
	insert(root, 5);
	
	in_order(root);
}