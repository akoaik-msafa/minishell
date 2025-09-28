/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/26 19:18:54 by akoaik           ###   ########.fr       */
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
		printf("minishell: %s: No such file or directory\n",node->args[0]);
		exit(127);
	}
	execve(cmd_path, node->args, get_env(env));
	perror(cmd_path);
	free(cmd_path);
	exit(127);
}

int	execute_builtin(tree_node *node, t_data *data)
{
	int		result;

	if (ft_strcmp(node->args[0], "cd") == 0)
	{
		result = ft_cd(node->args + 1, data->env, data->n_head);
	}
	else if (ft_strcmp(node->args[0], "pwd") == 0)
	{
		result = ft_pwd(node->args + 1);
	}
	else if (ft_strcmp(node->args[0], "echo") == 0)
	{
		result = ft_echo(node->args + 1);
	}
	else if (ft_strcmp(node->args[0], "export") == 0)
	{
		result = ft_export(node->args + 1, data->env, data->n_head, data->env_head);
	}
	else if(ft_strcmp(node->args[0], "unset") == 0)
	{
		result = ft_unset(node->args + 1, data->env);
	}
	else if(ft_strcmp(node->args[0], "env") == 0)
	{
		result = ft_env(node->args + 1, data->env);
	}
	else
	{
		result = -1;
	}
	return (result);
}

void	execute_command(tree_node *node, t_data *data)
{
	pid_t	pid;
	int		status;
	int		builtin_result;

	if (!node || !node->args || !node->args[0])
		return ;
	builtin_result = execute_builtin(node, data);
	if (builtin_result != -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(node, data->env);
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

void	execute_ast(tree_node *ast, t_data *data)
{
	if (!ast)
		return ;
	if (ast->type == cmd_node)
	{
		execute_command(ast, data);
	}
	else if (ast->type == pipe_node)
	{
		execute_pipe(ast, data);
	}
	else if (ast->type == redir_node)
	{
		if (ast->redir_type == t_re_heredoc)
			handle_heredoc_redirection(ast, data);
		else if (ast->redir_type == t_re_out)
			handle_output_redirection(ast, data);
	}
}
