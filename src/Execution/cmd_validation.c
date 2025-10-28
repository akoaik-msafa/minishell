/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 08:16:24 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 14:54:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_access_error(char *cmd_path)
{
	perror(cmd_path);
	exit(127);
}

static void	handle_permission_error(char *cmd_path)
{
	perror(cmd_path);
	free(cmd_path);
	exit(126);
}

static void	handle_directory_error(char *cmd_path)
{
	write(2, cmd_path, ft_strlen(cmd_path));
	write(2, ": Is a directory\n", 17);
	free(cmd_path);
	exit(126);
}

void	handle_cmd_not_found(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	exit(127);
}

int	validate_cmd_path(char *cmd_path)
{
	struct stat	path_stat;

	if (access(cmd_path, F_OK) != 0)
	{
		handle_access_error(cmd_path);
		return (0);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		handle_permission_error(cmd_path);
		return (0);
	}
	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		handle_directory_error(cmd_path);
		return (0);
	}
	return (1);
}
