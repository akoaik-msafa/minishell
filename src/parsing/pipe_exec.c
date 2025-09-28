/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/28 22:19:36 by akoaik           ###   ########.fr       */
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
		ast->left->heredoc_fd = here_doc(ast->left->filename);
		if (ast->left->heredoc_fd == -1)
			return;
	}
	if (ast->right && ast->right->type == redir_node && ast->right->redir_type == t_re_heredoc)
	{
		ast->right->heredoc_fd = here_doc(ast->right->filename);
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