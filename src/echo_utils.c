/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:05:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/14 15:46:59 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	calculate_total_length(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

void	copy_args_to_result(char **args, char *result)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (args[i])
	{
		strcpy(result + pos, args[i]);
		pos += strlen(args[i]);
		if (args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	result[pos] = '\0';
}
