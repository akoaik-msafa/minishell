/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:13:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 23:29:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_user_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && *input != '\0')
		add_history(input);
	return (input);
}
