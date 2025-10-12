/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:06:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 16:43:35 by akoaik           ###   ########.fr       */
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
	const char	*type_names[] = {"WORD", "BUILTIN", "ENV_BUILTIN", "PIPE",
			"REDIR_IN", "REDIR_OUT", "REDIR_APPEND", "REDIR_HEREDOC", "EOF"};
	int			i;

	printf("=== TOKEN EXPAND FLAG ANALYSIS ===\n");
	i = 0;
	while (i < count)
	{
		printf("Token %d: '%s' -> %s\n", i, tokens[i].str, type_names[tokens[i].type]);
		printf("  char expand_flag = %d ", tokens[i].expand_flag);
		if (tokens[i].expand_flag == 0)
			printf("(NO expansion - quoted or operator)\n");
		else
			printf("(expansion ENABLED - unquoted)\n");

		// Special case for heredoc delimiters
		if (i > 0 && tokens[i-1].type == t_re_heredoc)
		{
			printf("  -> This is a HEREDOC DELIMITER\n");
			printf("  -> Will be stored in AST node's expand_flags[0]\n");
		}
		printf("\n");
		i++;
	}
	printf("=====================================\n");
}

void	print_indent(int depth)
{
	int i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_ast(tree_node *node, int depth)
{
	const char	*node_types[] = {"CMD", "PIPE", "REDIRECT"};
	const char	*redir_types[] = {"WORD", "BUILTIN", "PIPE", "REDIR_IN",
			"REDIR_OUT", "REDIR_APPEND", "REDIR_HEREDOC", "EOF"};
	int			i;

	if (!node)
		return ;

	print_indent(depth);
	printf("Node: %s\n", node_types[node->type]);

	// Show expand_flags information for all nodes
	print_indent(depth);
	printf("expand_flags: ");
	if (node->expand_flags)
	{
		printf("allocated -> [0]=%d", node->expand_flags[0]);
		if (node->expand_flags[0] == 0)
			printf(" (NO expansion)");
		else
			printf(" (expansion ENABLED)");
		printf("\n");
	}
	else
	{
		printf("NULL (no expand info stored)\n");
	}

	if (node->type == cmd_node && node->args)
	{
		print_indent(depth + 1);
		printf("Args: ");
		i = 0;
		while (node->args[i])
		{
			printf("%s ", node->args[i]);
			i++;
		}
		printf("\n");
	}

	// Show redirection details with expand flag analysis
	if (node->type == redir_node)
	{
		print_indent(depth + 1);
		printf("Redirection: %s -> '%s'\n", redir_types[node->redir_type], node->filename);

		if (node->redir_type == t_re_heredoc)
		{
			print_indent(depth + 1);
			printf("*** HEREDOC DELIMITER ANALYSIS ***\n");
			print_indent(depth + 1);
			printf("Delimiter: '%s'\n", node->filename);
			print_indent(depth + 1);
			if (node->expand_flags)
			{
				printf("expand_flags[0] = %d -> ", node->expand_flags[0]);
				if (node->expand_flags[0] == 0)
					printf("Content will NOT be expanded (quoted delimiter)\n");
				else
					printf("Content WILL be expanded (unquoted delimiter)\n");
			}
			else
			{
				printf("expand_flags = NULL -> Will default to expansion\n");
			}
			print_indent(depth + 1);
			printf("**********************************\n");
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



void print_tree(tree_node *node, int depth)
{
	int i;

	if (!node)
		return;

	for (i = 0; i < depth; i++)
		printf("  ");

	if (node->type == cmd_node)
	{
		printf("CMD_NODE: ");
		if (node->args && node->args[0])
			printf("%s\n", node->args[0]);
		else
			printf("(empty)\n");
	}
	else if (node->type == pipe_node)
	{
		printf("PIPE_NODE\n");
		if (node->left)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("left:\n");
			print_tree(node->left, depth + 2);
		}
		if (node->right)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("right:\n");
			print_tree(node->right, depth + 2);
		}
	}
	else if (node->type == redir_node)
	{
		printf("REDIR_NODE: ");
		if (node->redir_type == t_re_heredoc)
			printf("<<");
		else if (node->redir_type == t_re_out)
			printf(">");
		else if (node->redir_type == t_re_append)
			printf(">>");
		else if (node->redir_type == t_re_in)
			printf("<");

		if (node->filename)
			printf(" %s\n", node->filename);
		else
			printf(" (no file)\n");

		if (node->left)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("left:\n");
			print_tree(node->left, depth + 2);
		}
	}
}