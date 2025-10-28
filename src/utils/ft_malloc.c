/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:37:57 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/17 22:34:50 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_malloc(size_t size, t_list_head *n_head)
{
	void				*ptr;
	struct s_alloc_list	*node;

	if (!n_head)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(struct s_alloc_list));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->allocation = ptr;
	node->next = n_head->head;
	n_head->head = node;
	return (ptr);
}

void	free_all(t_list_head *n_head)
{
	struct s_alloc_list	*tmp;
	struct s_alloc_list	*current;

	if (!n_head)
		return ;
	current = n_head->head;
	while (current)
	{
		free(current->allocation);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	n_head->head = NULL;
}
