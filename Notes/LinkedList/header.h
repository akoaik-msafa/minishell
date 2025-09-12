/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:20:32 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/05 02:34:34 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

struct alloc_list
{
    void *allocation;
    struct alloc_list *next;
};

struct meta_data {
	struct alloc_lis *head ;
};

void *ft_malloc(size_t size, struct alloc_list **head);
void free_all(struct alloc_list *head);
