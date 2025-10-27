/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 23:04:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	child1(t_tree_node *cmd_node, int *pipefd, t_data *data)
{
	if (dup2(pipefd[1], 1) < 0)
	{
		perror("dup2 pipe write error");
		exit(1);
	}
	close(pipefd[0]);
	execute_ast(cmd_node, data);
	exit(data->exit_code);
}

int	child2(t_tree_node *cmd_node, int *pipefd, t_data *data)
{
	if (dup2(pipefd[0], 0) < 0)
	{
		perror("dup2 pipe read error");
		exit(1);
	}
	close(pipefd[1]);
	execute_ast(cmd_node, data);
	exit(data->exit_code);
}

int	collect_heredocs(t_tree_node *node, t_data *data)
{
	if (!node)
		return (0);
	if (node->type == redir_node && node->redir_type == t_re_heredoc)
		return (process_heredoc_node(node, data));
	if (node->type == pipe_node)
		return (process_pipe_node(node, data));
	if (node->type == redir_node)
		return (collect_heredocs(node->left, data));
	return (0);
}

void	execute_pipe(t_tree_node *ast, t_data *data)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	set_exit_code_from_status(data, status);
}
