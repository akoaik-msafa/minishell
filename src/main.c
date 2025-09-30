/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/30 17:02:22 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_all_debug(token_t *tokens, int token_count, tree_node *ast)
{
	printf("=== TOKENS ===\n");
	print_tokens(tokens, token_count);
	printf("===============\n");
	printf("=== AST TREE STRUCTURE ===\n");
	print_tree(ast, 0);
	printf("===========================\n");
}

void	while_prompt(t_list_head *n_head, t_list_head *env_head, t_env *env)
{
	char		*prompt;
	token_t		*tokens;
	tree_node	*ast;
	t_data		data;

	init_data(&data, n_head, env, env_head);

	while (1)
	{
		prompt = get_user_input();
		if (!prompt)
			break ;
		temp_exit(prompt, n_head, env_head);
		tokens = tokenize_input(prompt, &data);
		if (!tokens)
		{
			free(prompt);
			free_all(n_head);
			n_head->head = NULL;
		}
		else
		{
			int token_count = count_token_array(tokens);
			ast = parse_tokens(tokens, token_count, n_head, env);
			// print_all_debug(tokens, token_count, ast);
			if (ast)
				execute_ast(ast, &data);
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
		- Signals handling
		- exit codes
	leaks :
	- when run another shell, the SHLVL should increment. 
	export contains two lines of each variable

    test : 
    echo "m"y H"ome i"s $"HOME" > f1 | cat <<EOF > f2 | cat <<"EOF" > f3 | ls > ls | cat f1 | cat f2 | cat f3 | cat ls > ls | cat ls`
*/