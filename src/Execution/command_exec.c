/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/23 19:31:43 by akoaik           ###   ########.fr       */
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

int	execute_builtin(tree_node *node, t_env *env, t_list_head *n_head,
		t_list_head *env_head)
{
	char	*combined_args;
	int		result;

	combined_args = NULL;
	if (node->args[1])
	{
		combined_args = join_args(node->args + 1);
	}
	if (ft_strcmp(node->args[0], "cd") == 0)
	{
		result = ft_cd(combined_args, env, n_head);
	}
	else if (ft_strcmp(node->args[0], "pwd") == 0)
	{
		result = ft_pwd(combined_args);
	}
	else if (ft_strcmp(node->args[0], "echo") == 0)
	{
		result = ft_echo(combined_args);
	}
	else if (ft_strcmp(node->args[0], "export") == 0)
	{
		result = ft_export(combined_args, env, n_head, env_head);
	}
	else
	{
		result = -1;
	}
	if (combined_args)
		free(combined_args);
	return (result);
}

void	execute_command(tree_node *node, t_env *env, t_list_head *n_head,
		t_list_head *env_head)
{
	pid_t	pid;
	int		status;
	int		builtin_result;

	if (!node || !node->args || !node->args[0])
		return ;
	builtin_result = execute_builtin(node, env, n_head, env_head);
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

void	execute_ast(tree_node *ast, t_env *env, t_list_head *n_head,
		t_list_head *env_head)
{
	if (!ast)
		return ;
	if (ast->type == cmd_node)
	{
		execute_command(ast, env, n_head, env_head);
	}
	else if (ast->type == pipe_node)
	{
		execute_pipe(ast, env, n_head, env_head);
	}
}
