/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:48:25 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/28 15:01:47 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp ;

	if (!lst | !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new ;
		return ;
	}
	temp = *lst ;
	while (temp->next != NULL)
		temp = temp->next ;
	temp->next = new ;
}
