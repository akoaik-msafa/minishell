/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/05 04:36:34 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void 	increment_shell_level(t_env *env,t_data *data)
// {
// 	int index;
// 	int old_value;
// 	int new_value;
// 	char *new_shlvl;
	
// 	index = find_env_var("SHLVL=",env->export_only);
// 	old_value = ft_atoi(env->export_only[index] + 6);
// 	new_value = old_value + 1;
// 	new_shlvl = ft_strjoin("SHLVL=",ft_itoa(new_value));
// 	update_export(new_shlvl,env,index,data->env_head);
// }
void	exec_cmd(tree_node *node, t_env *env)
{
	char	*cmd_path;

	if (!node || !node->args || !node->args[0])
		exit(127);
	cmd_path = get_cmd_path(node->args[0], env);
	if (!cmd_path)
	{
		printf("minishell: %s: command not found\n", node->args[0]);
		exit(127);
	}
	// if(ft_strncmp(node->args[0],"./minishell",ft_strlen(node->args[0]) + 1) == 0)
	// 		increment_shell_level(env,data);
	execve(cmd_path, node->args, get_env(env));
	perror(cmd_path);
	free(cmd_path);
	exit(127);
}

int	execute_builtin(tree_node *node, t_data *data)
{
	int	result;

	if (ft_strcmp(node->args[0], "cd") == 0)
		result = ft_cd(node->args + 1, data->env, data->n_head);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		result = ft_pwd(node->args + 1);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		result = ft_echo(node->args + 1);
	else if (ft_strcmp(node->args[0], "export") == 0)
		result = ft_export(node->args + 1, data->env, data->n_head,
				data->env_head);
	else if (ft_strcmp(node->args[0], "unset") == 0)
	{
		result = ft_unset(node->args + 1, data->env);
	}
	else if (ft_strcmp(node->args[0], "env") == 0)
	{
		result = ft_env(node->args + 1, data->env);
	}
	else if (ft_strcmp(node->args[0], "exit") == 0)
	{
		result = ft_exit(node->args, data);
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
	{
		data->exit_code = builtin_result;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(node, data->env);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		set_exit_code_from_status(data, status);
	}
	else
	{
		perror("fork");
		data->exit_code = 1;
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
		else if (ast->redir_type == t_re_append)
			handle_append_redirection(ast, data);
		else if (ast->redir_type == t_re_in)
			handle_redirection_input(ast, data);
	}
}
