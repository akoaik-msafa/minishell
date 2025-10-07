/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:45:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/07 20:20:25 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_cmd(tree_node *node, t_env *env)
{
	char			*cmd_path;
	struct stat		path_stat;

	if (!node || !node->args || !node->args[0])
		exit(127);
		
	cmd_path = get_cmd_path(node->args[0], env);
	if (!cmd_path)
	{
		write(2, node->args[0], ft_strlen(node->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (access(cmd_path, F_OK) != 0)
	{
		perror(cmd_path);
		exit(127);		
	}
	if (access(cmd_path, X_OK) != 0)
	{
		perror(cmd_path);
		free(cmd_path);
		exit(126);
	}
	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		write(2, cmd_path, ft_strlen(cmd_path));
		write(2, ": Is a directory\n", 17);
		free(cmd_path);
		exit(126);
	}
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
		result = ft_export(node->args + 1, data);
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
		result = ft_exit(node->args + 1, data);
	}
	else
	{
		result = -1;
	}
	return (result);
}

void	execute_command(tree_node *node, t_data *data)
{
	pid_t				pid;
	int					status;
	int					builtin_result;
	struct sigaction	sa;

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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd(node, data->env);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		init_sigaction(&sa);
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
		if (ast->args[0] && !ast->args[0][0])
		{
			ast->args = ast->args +  1;
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
