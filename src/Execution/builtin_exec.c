/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 00:00:00 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	execute_cd_pwd_echo(tree_node *node, t_data *data)
{
	if (ft_strcmp(node->args[0], "cd") == 0)
		return (ft_cd(node->args + 1, data->env, data->n_head));
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		return (ft_pwd(node->args + 1));
	else if (ft_strcmp(node->args[0], "echo") == 0)
		return (ft_echo(node->args + 1));
	return (-1);
}

static int	execute_export_unset_env(tree_node *node, t_data *data)
{
	if (ft_strcmp(node->args[0], "export") == 0)
		return (ft_export(node->args + 1, data));
	else if (ft_strcmp(node->args[0], "unset") == 0)
		return (ft_unset(node->args + 1, data->env));
	else if (ft_strcmp(node->args[0], "env") == 0)
		return (ft_env(node->args + 1, data->env));
	return (-1);
}

int	execute_builtin(tree_node *node, t_data *data)
{
	int	result;

	result = execute_cd_pwd_echo(node, data);
	if (result != -1)
		return (result);
	result = execute_export_unset_env(node, data);
	if (result != -1)
		return (result);
	if (ft_strcmp(node->args[0], "exit") == 0)
		return (ft_exit(node->args + 1, data));
	return (-1);
}
