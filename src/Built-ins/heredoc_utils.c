/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:48:13 by msafa             #+#    #+#             */
/*   Updated: 2025/10/27 22:49:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	check_heredoc_status(int status, t_data *data)
{
	struct sigaction	sa;

	init_sigaction(&sa);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->exit_code = 130;
		write(1, "\n", 1);
		return (-1);
	}
	return (0);
}

int	open_heredoc_file(char *temp_file, int saved_stdin)
{
	int	fd_write;

	fd_write = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_write == -1)
	{
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		return (-1);
	}
	return (fd_write);
}
