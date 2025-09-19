/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/19 19:06:36 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	while_prompt(t_list_head *n_head, t_list_head *env_head,
		t_env *env)
{
	char		*prompt;
	token_t		*tokens;
	int			token_count;
	tree_node	*ast;
	
	while (1)
	{
		prompt = get_user_input();
		if (!prompt)
			break ;
		temp_exit(prompt, n_head, env_head);
		tokens = tokenize_input(prompt, &token_count, n_head);
		ast = parse_tokens(tokens, token_count, n_head, env);
		if (ast)
			execute_ast(ast, env);
		free(prompt);
		free_all(n_head);
		n_head->head = NULL;
	}
	free_all(env_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_list_head		n_head;
	t_list_head		env_head;
	t_env				env;

	n_head.head = NULL;
	env_head.head = NULL;
	(void)argc;
	(void)argv;
	if (!init_env(&env, envp, &env_head))
	{
		return (1);
	}
	// n_head.env = &env;
	while_prompt(&n_head, &env_head, &env);
	free_all(&env_head);
}

/*

	I still have : 
		- expanding
		- quotes 
		- exit codes
	to check it : 
		- expand.c file 
		- ft_split.c 

*/