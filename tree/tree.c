/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:17:23 by msafa             #+#    #+#             */
/*   Updated: 2025/09/05 22:39:31 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_tree
{
	int value;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

// creating the root

t_tree *create_root(int value)
{
	t_tree *root = malloc(sizeof(t_tree));
	if(!root)
		return NULL;
	root->value = value;
	root->left = NULL;
	root->right  = NULL;
	return root;
}

t_tree *insert_childs(t_tree *root,int value)
{
	// base case : 
	if (root == NULL )
	{
		return create_root(value);
	}
	if(value > root->value)
		root->right = insert_childs(root->right, value); // <-- call 
	if(value < root->value)
		root->left =  insert_childs(root->left, value);   // <-- call 
	return root ;
}

void in_order(t_tree *root)
{
	if(root == NULL)
		return ;
	in_order(root->left);
	printf("%d ",root->value);
	in_order(root->right);
	
}

void pre_order(t_tree *root)
{
	if(root == NULL)
		return ;
	printf("%d ",root->value);
	pre_order(root->left);
	pre_order(root->right);
}


int main(void)
{
	t_tree *root = create_root(8);
	insert_childs(root, 1);
	insert_childs(root, 4);
	insert_childs(root, 3);
	insert_childs(root, 2);
	insert_childs(root, 8);
	insert_childs(root, 6);

	in_order(root);
	printf("\n");
	pre_order(root);
	free(root);
	return 0;
}
