/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/05 17:33:53 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Sets the exit code in the data structure based on a process status.
** Handles two cases:
** 1. Normal exit: extracts the exit status code (0-255)
** 2. Signal termination: calculates exit code as 128 + signal number
**    (e.g., SIGINT (2) becomes 130, SIGTERM (15) becomes 143)
*/
void	set_exit_code_from_status(t_data *data, int status)
{
	if (!data)
		return ;
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		data->exit_code = 128 + WTERMSIG(status);
	}
}
