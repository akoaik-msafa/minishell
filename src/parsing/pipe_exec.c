/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/29 02:47:43 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	child1(tree_node *cmd_node, int *pipefd, t_data *data)
{
	if (dup2(pipefd[1], 1) < 0)
	{
		perror("dup2 pipe write error");
		exit(1);
	}
	close(pipefd[0]);
	execute_ast(cmd_node, data);
	exit(0);
}

int	child2(tree_node *cmd_node, int *pipefd, t_data *data)
{
	if (dup2(pipefd[0], 0) < 0)
	{
		perror("dup2 pipe read error");
		exit(1);
	}
	close(pipefd[1]);
	execute_ast(cmd_node, data);
	exit(0);
}

void	execute_pipe(tree_node *ast, t_data *data)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	// Handle heredoc in parent process before fork
	if (ast->left && ast->left->type == redir_node && ast->left->redir_type == t_re_heredoc)
	{
		int expand_flag;
		printf("\n=== PIPE LEFT HEREDOC EXPAND FLAG CONVERSION ===\n");
		printf("Left AST node filename: '%s'\n", ast->left->filename);
		printf("Left AST node expand_flags: ");
		if (ast->left->expand_flags)
		{
			printf("allocated\n");
			printf("  char expand_flags[0] = %d\n", ast->left->expand_flags[0]);
			expand_flag = ast->left->expand_flags[0];  // char -> int conversion
			printf("  Converting to int expand_flag = %d\n", expand_flag);
			printf("  Source: From delimiter token in pipe left side\n");
		}
		else
		{
			printf("NULL\n");
			expand_flag = 1;
			printf("  Using default int expand_flag = %d\n", expand_flag);
		}
		printf("  Result: Heredoc content will%s be expanded\n", expand_flag ? "" : " NOT");
		printf("================================================\n");
		ast->left->heredoc_fd = here_doc(ast->left->filename, data, expand_flag);
		if (ast->left->heredoc_fd == -1)
			return;
	}
	if (ast->right && ast->right->type == redir_node && ast->right->redir_type == t_re_heredoc)
	{
		int expand_flag;
		printf("\n=== PIPE RIGHT HEREDOC EXPAND FLAG CONVERSION ===\n");
		printf("Right AST node filename: '%s'\n", ast->right->filename);
		printf("Right AST node expand_flags: ");
		if (ast->right->expand_flags)
		{
			printf("allocated\n");
			printf("  char expand_flags[0] = %d\n", ast->right->expand_flags[0]);
			expand_flag = ast->right->expand_flags[0];  // char -> int conversion
			printf("  Converting to int expand_flag = %d\n", expand_flag);
			printf("  Source: From delimiter token in pipe right side\n");
		}
		else
		{
			printf("NULL\n");
			expand_flag = 1;
			printf("  Using default int expand_flag = %d\n", expand_flag);
		}
		printf("  Result: Heredoc content will%s be expanded\n", expand_flag ? "" : " NOT");
		printf("=================================================\n");
		ast->right->heredoc_fd = here_doc(ast->right->filename, data, expand_flag);
		if (ast->right->heredoc_fd == -1)
			return;
	}

	if (pipe(pipefd) < 0)
	{
		perror("pipe failed");
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
		child1(ast->left, pipefd, data);
	pid2 = fork();
	if (pid2 == 0)
		child2(ast->right, pipefd, data);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
}