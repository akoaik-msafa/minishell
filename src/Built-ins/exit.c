/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:50:40 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/02 18:50:41 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_exit(char **args, t_data *data)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "exit") == 0)
		exit(data->exit_code);
	return (0);
}
