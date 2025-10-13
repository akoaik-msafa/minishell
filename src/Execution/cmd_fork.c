/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 00:00:00 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_child_process(tree_node *node, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec_cmd(node, data->env);
}

static void	handle_parent_process(pid_t pid, t_data *data)
{
	int					status;
	struct sigaction	sa;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_sigaction(&sa);
	set_exit_code_from_status(data, status);
}

void	fork_and_execute(tree_node *node, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(node, data);
	else if (pid > 0)
		handle_parent_process(pid, data);
	else
	{
		perror("fork");
		data->exit_code = 1;
	}
}
