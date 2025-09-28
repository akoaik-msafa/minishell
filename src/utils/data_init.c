/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:51:40 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/28 15:51:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data(t_data *data, t_list_head *n_head, t_env *env, t_list_head *env_head)
{
	if (!data)
		return ;
	data->n_head = n_head;
	data->env = env;
	data->env_head = env_head;
}