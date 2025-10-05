/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:13:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/05 16:58:27 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*read_from_pipe(void)
{
	char	buffer[10000];
	int		i;
	int		bytes_read;
	char	*line;

	i = 0;
	while (i < 9999)
	{
		bytes_read = read(STDIN_FILENO, &buffer[i], 1);
		if (bytes_read <= 0)
			return (NULL);
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

char	*get_user_input(void)
{
	char	*input;

	if (isatty(STDIN_FILENO))
	{
		input = readline("minishell$ ");
		if (input && *input != '\0')
			add_history(input);
	}
	else
	{
		printf("minishell$ \n");
		input = read_from_pipe();
	}
	return (input);
}
