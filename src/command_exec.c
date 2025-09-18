/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 02:21:07 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_cmd(tree_node *node, t_env *env)
{
	char	*cmd_path;

	if (!node || !node->args || !node->args[0])
		exit(127);
	cmd_path = get_cmd_path(node->args[0], env);
	if (!cmd_path)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
	execve(cmd_path, node->args, get_env(env));
	perror(cmd_path);
	free(cmd_path);
	exit(127);
}

void	execute_command(tree_node *node, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!node || !node->args || !node->args[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(node, env);
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

void	execute_ast(tree_node *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == cmd_node)
	{
		execute_command(ast, env);
	}
	else if (ast->type == pipe_node)
	{
		execute_pipe(ast, env);
	}
}