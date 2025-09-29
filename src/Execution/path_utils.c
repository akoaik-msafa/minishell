/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:07:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/29 18:37:45 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_split(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	*find_path_env(t_env *env)
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

char	*build_full_path(char *dir, char *cmd)
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

char	*search_in_paths(char **paths, char *cmd)
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
			continue ;
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

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_env;

	if (!cmd || cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_env = find_path_env(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
