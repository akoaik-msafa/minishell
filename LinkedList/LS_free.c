/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LS_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:11:58 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/05 02:32:43 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "header.h"

void *ft_malloc(size_t size, struct alloc_list **head)
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
    node->next = *head;
    *head = node;

    return ptr;
}

void free_all(struct alloc_list *head)
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
