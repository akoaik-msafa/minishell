/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 03:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/23 13:38:49 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	child1(tree_node *cmd_node, int *pipefd, t_env *env, t_list_head *n_head, t_list_head *env_head)
{
	if (dup2(pipefd[1], 1) < 0)
	{
		perror("dup2 pipe write error");
		exit(1);
	}
	close(pipefd[0]);
	execute_ast(cmd_node, env, n_head, env_head);
	exit(0);
}

int	child2(tree_node *cmd_node, int *pipefd, t_env *env, t_list_head *n_head, t_list_head *env_head)
{
	if (dup2(pipefd[0], 0) < 0)
	{
		perror("dup2 pipe read error");
		exit(1);
	}
	close(pipefd[1]);
	execute_ast(cmd_node, env, n_head, env_head);
	exit(0);
}

void	execute_pipe(tree_node *ast, t_env *env, t_list_head *n_head,t_list_head *env_head)
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
		child1(ast->left, pipefd, env, n_head, env_head);
	pid2 = fork();
	if (pid2 == 0)
		child2(ast->right, pipefd, env, n_head, env_head);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
}