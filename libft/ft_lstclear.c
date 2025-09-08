/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:56:51 by akoaik            #+#    #+#             */
/*   Updated: 2025/05/29 15:17:29 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*second;
// 	t_list	*third;

// 	head = ft_lstnew(ft_strdup("Node 1"));
// 	second = ft_lstnew(ft_strdup("Node 2"));
// 	third = ft_lstnew(ft_strdup("Node 3"));
// 	if (!head || !second || !third)
// 		return (1);
// 	head->next = second;
// 	second->next = third;
// 	printf("Before clear: %s\n", (char *)head->content);
// 	ft_lstclear(&head, del);
// 	if (!head)
// 		printf("List successfully cleared.\n");
// 	else
// 		printf("Clear failed.\n");
// 	return (0);
// }
