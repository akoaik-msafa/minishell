/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 23:12:11 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/11 23:28:55 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/wait.h>

static void	execute_command(tree_node *node)
{
	pid_t	pid;
	int		status;

	if (!node || !node->args || !node->args[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (execvp(node->args[0], node->args) == -1)
		{
			perror("minishell");
			exit(127);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}

void	execute_ast(tree_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == node_cmd)
	{
		execute_command(ast);
	}
}