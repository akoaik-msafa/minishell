/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 16:59:25 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	struct list_head	n_head;
	char				*prompt;
	tree_node			*root;

	n_head.head = NULL;
	while (1)
	{
		prompt = get_user_input();
		if (!prompt)
			continue ;
		add_history(prompt);
		printf("user input is : %s\n", prompt);
		root = creat_node(node_cmd, &n_head);
		root->args = ft_malloc(sizeof(char *) * 2, &n_head);
		root->args[0] = my_strdup("ls", &n_head);
		root->args[1] = NULL;
		if (!ft_strncmp(prompt, "exit", 4))
		{
			free(prompt);
			free_all(&n_head);
			rl_clear_history();
			exit(0);
		}	rl_clear_history();
	rl_reset_terminal(NULL);
		free(prompt);
	}
	free_all(&n_head);
	rl_clear_history();
	rl_reset_terminal(NULL);
}
