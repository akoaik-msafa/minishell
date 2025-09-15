/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 23:12:11 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/15 14:43:01 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	free_split(char **strs)
{
	int	i;

	if (!strs)
		return;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

static char	*find_path_env(t_env *env)
{
	char	**envp;
	int		i;

	envp = get_env(env);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = build_full_path(paths[i], cmd);
		if (!path)
		{
			i++;
			continue;
		}
		if (access(path, X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_env;

	if (!cmd || cmd[0] == '/' || cmd[0] == '.')
		return (my_strdup(cmd, NULL));
	path_env = find_path_env(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}

static void	exec_cmd(tree_node *node, t_env *env)
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

static int	child1(tree_node *cmd_node, int *pipefd, t_env *env)
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

static int	child2(tree_node *cmd_node, int *pipefd, t_env *env)
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

static void	execute_command(tree_node *node, t_env *env)
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

static void	execute_pipe(tree_node *ast, t_env *env)
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

void	execute_ast(tree_node *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == node_cmd)
	{
		execute_command(ast, env);
	}
	else if (ast->type == node_pipe)
	{
		execute_pipe(ast, env);
	}
}