/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:13:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/17 22:34:18 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_user_input(void)
{
	char	*input;

	input = readline("-My_minishell ~>");
	if (input && *input != '\0')
	{
		add_history(input);
	}
	return (input);
}

void	temp_exit(char *str, t_list_head *n_head,
		t_list_head *env_head)
{
	if (!ft_strncmp(str, "exit", 4))
	{
		free_all(n_head);
		free_all(env_head);
		exit(1);
	}
}
