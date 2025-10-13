/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 19:35:33 by akoaik           ###   ########.fr       */
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
		handle_cmd_not_found(node->args[0]);
	validate_cmd_path(cmd_path);
	execve(cmd_path, node->args, env->export_only);
	perror(cmd_path);
	free(cmd_path);
	exit(127);
}

void	execute_command(tree_node *node, t_data *data)
{
	int	builtin_result;

	if (!node || !node->args || !node->args[0])
		return ;
	builtin_result = execute_builtin(node, data);
	if (builtin_result != -1)
	{
		data->exit_code = builtin_result;
		return ;
	}
	fork_and_execute(node, data);
}

void	execute_ast(tree_node *ast, t_data *data)
{
	if (!ast)
		return ;
	if (ast->type == cmd_node)
	{
		if (ast->args[0] && !ast->args[0][0])
		{
			ast->args = ast->args + 1;
		}
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
		else if (ast->redir_type == t_re_append)
			handle_append_redirection(ast, data);
		else if (ast->redir_type == t_re_in)
			handle_redirection_input(ast, data);
	}
}
