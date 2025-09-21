/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/21 05:34:35 by akoaik           ###   ########.fr       */
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

int	execute_builtin(tree_node *node, t_env *env,t_list_head *n_head)
{
	if (!node || !node->args || !node->args[0])
		return (0);
	if (strcmp(node->args[0], "cd") == 0)
	{
		return (ft_cd(node->args[1], env,n_head));
	}
	if(strcmp(node->args[0],"pwd") == 0)
	{
		return(ft_pwd(node->args[1]));
	}
	return (-1);
}

void	execute_command(tree_node *node, t_env *env,t_list_head *n_head)
{
	pid_t	pid;
	int		status;
	int		builtin_result;

	if (!node || !node->args || !node->args[0])
		return ;
	builtin_result = execute_builtin(node, env,n_head);
	if (builtin_result != -1)
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

void	execute_ast(tree_node *ast, t_env *env,t_list_head *n_head)
{
	if (!ast)
		return ;
	if (ast->type == cmd_node)
	{
		execute_command(ast, env,n_head);
	}
	else if (ast->type == pipe_node)
	{
		execute_pipe(ast, env, n_head);
	}
}