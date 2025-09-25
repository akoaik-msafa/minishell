/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/25 18:18:59 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	while_prompt(t_list_head *n_head, t_list_head *env_head, t_env *env)
{
	char		*prompt;
	token_t		*tokens;
	tree_node	*ast;
	static int	loop_count = 0;

	while (1)
	{
		loop_count++;
		printf("LOOP %d:\n", loop_count);
		prompt = get_user_input();
		if (!prompt)
			break ;
		temp_exit(prompt, n_head, env_head);
		tokens = tokenize_input(prompt, n_head);
		if (!tokens)
		{
			free(prompt);
			free_all(n_head);
			n_head->head = NULL;
		}
		else
		{
			printf("=== TOKENS ===\n");
			// print_tokens(tokens, token_count);
			printf("===============\n");
			ast = parse_tokens(tokens, token_count, n_head, env);
			print_tree_structure(ast);
			if (ast)
				execute_ast(ast, env, n_head,env_head);
			free(prompt);
			free_all(n_head);
			n_head->head = NULL;
		}
	}
	free_all(env_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_list_head	n_head;
	t_list_head	env_head;
	t_env		env;

	n_head.head = NULL;
	env_head.head = NULL;
	(void)argc;
	(void)argv;
	if (!init_env(&env, envp, &env_head))
	{
		return (1);
	}
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
	leaks :
		echo as built-in still use malloc
		not ft_malloc

cases :
		- in echo we have "hello "" world "
		- export : a=12 after export should change the value of a
		- export a / export a=
		- unset env --> the env should display a new line not command not found
*/