/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/02 23:31:19 by msafa            ###   ########.fr       */
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

void	collect_heredocs(tree_node *node, t_data *data)
{
	int expand_flag;

	if (!node)
		return;
	if (node->type == redir_node && node->redir_type == t_re_heredoc)
	{
		if (node->heredoc_fd == -1)
		{
			if (node->expand_flags)
				expand_flag = node->expand_flags[0];
			else
				expand_flag = 1;
			node->heredoc_fd = here_doc(node->filename, data, expand_flag);
		}
		collect_heredocs(node->left, data);
	}
	else if (node->type == pipe_node)
	{
		collect_heredocs(node->left, data);
		collect_heredocs(node->right, data);
	}
	else if (node->type == redir_node)
	{
		collect_heredocs(node->left, data);
	}
}

void	execute_pipe(tree_node *ast, t_data *data)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	// Collect all heredocs in the entire tree before forking
	collect_heredocs(ast, data);

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
	set_exit_code_from_status(data, status);
}