/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LS_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:11:58 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/04 02:21:12 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

struct alloc_list
{
    void *allocation;
    struct alloc_list *next;
};

struct alloc_list *head = NULL;

void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;

    struct alloc_list *node = malloc(sizeof(struct alloc_list));
    if (!node)
    {
        free(ptr);
        return NULL;
    }
    node->allocation = ptr;
    node->next = head;
    head = node;

    return ptr;
}

void free_all()
{
    struct alloc_list *tmp;
    while (head)
    {
        free(head->allocation);
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
