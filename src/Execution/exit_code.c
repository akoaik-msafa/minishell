/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 04:43:09 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 01:15:49 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
