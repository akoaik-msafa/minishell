/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:20:18 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/05 02:33:10 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

int all(struct alloc_list **head)
{
    char *test = ft_malloc(sizeof(int), head);
    if (!test)
        return 0;
    return 1;
}

int main()
{
    struct alloc_list *head = NULL;
    printf("%i\n", all(&head));
    free_all(head);
    return 0;
}
