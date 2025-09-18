/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:06:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 02:16:38 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_tokens(token_t *tokens, int count)
{
	const char	*type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
			"REDIR_APPEND", "REDIR_HEREDOC", "EOF"};
	int			i;

	i = 0;
	while (i < count)
	{
		printf("Token %d: '%s' -> %s\n", i, tokens[i].str,
			type_names[tokens[i].type]);
		i++;
	}
}

void	print_ast(tree_node *node, int depth)
{
	const char	*node_types[] = {"CMD", "PIPE", "REDIRECT"};
	const char	*redir_types[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
		"REDIR_APPEND", "REDIR_HEREDOC", "EOF"};
	int			i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("Node: %s\n", node_types[node->type]);
	if (node->type == cmd_node && node->args)
	{
		i = 0;
		while (i < depth + 1)
		{
			printf("  ");
			i++;
		}
		printf("Args: ");
		i = 0;
		while (node->args[i])
		{
			printf("'%s' ", node->args[i]);
			i++;
		}
		printf("\n");
		if (node->redir_type != t_eof && node->filename)
		{
			i = 0;
			while (i < depth + 1)
			{
				printf("  ");
				i++;
			}
			printf("Redirection: %s -> '%s'\n", redir_types[node->redir_type], node->filename);
		}
	}
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}

void	print_tree_structure(tree_node *ast)
{
	if (!ast)
	{
		printf("No AST created - parsing failed\n");
		return ;
	}
	printf("=== COMMAND TREE STRUCTURE ===\n");
	print_ast(ast, 0);
	printf("===============================\n");
}