/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 02:22:10 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	child1(tree_node *cmd_node, int *pipefd, t_env *env)
{
	if (dup2(pipefd[1], 1) < 0)
	{
		perror("dup2 pipe write error");
		exit(1);
	}
	close(pipefd[0]);
	exec_cmd(cmd_node, env);
	return (1);
}

int	child2(tree_node *cmd_node, int *pipefd, t_env *env)
{
	if (dup2(pipefd[0], 0) < 0)
	{
		perror("dup2 pipe read error");
		exit(1);
	}
	close(pipefd[1]);
	execute_ast(cmd_node, env);
	exit(0);
}

void	execute_pipe(tree_node *ast, t_env *env)
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
		child1(ast->left, pipefd, env);
	pid2 = fork();
	if (pid2 == 0)
		child2(ast->right, pipefd, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
}