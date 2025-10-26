/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/26 23:20:09 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			g_signal;

static void	process_prompt(char *prompt, t_list_head *n_head, t_data *data)
{
	token_t		*tokens;
	tree_node	*ast;
	int			token_count;

	tokens = tokenize_input(prompt, data);
	if (!tokens)
	{
		free(prompt);
		free_all(n_head);
		n_head->head = NULL;
	}
	else
	{
		token_count = count_token_array(tokens);
		ast = parse_tokens(tokens, token_count, n_head, data);
		if (ast)
		{
			execute_ast(ast, data);
		}
		free(prompt);
		free_all(n_head);
		n_head->head = NULL;
	}
}

int	while_prompt(t_list_head *n_head, t_list_head *env_head, t_env *env)
{
	char	*prompt;
	t_data	data;

	init_data(&data, n_head, env, env_head);
	while (1)
	{
		prompt = get_user_input();
		if (!prompt)
			break ;
		if (g_signal != 0)
		{
			data.exit_code = g_signal;
			g_signal = 0;
		}
		process_prompt(prompt, n_head, &data);
	}
	free_all(env_head);
	return (data.exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_list_head			n_head;
	t_list_head			env_head;
	t_env				env;
	struct sigaction	sa;

	n_head.head = NULL;
	env_head.head = NULL;
	g_signal = 0;
	(void)argc;
	(void)argv;
	if (!init_env(&env, envp, &env_head))
	{
		return (1);
	}
	init_sigaction(&sa);
	while_prompt(&n_head, &env_head, &env);
	free_all(&env_head);
	return (0);
}

/*
	I still have :
		- Signals handling
		- exit codes

	Cases :
		- in the export when i add export a= and
		after that i change the value
		if a using export a=12 it is not change
	leaks :
	export not changed

	test :
	1- echo "m"y H"ome i"s $"HOME" > f1 | cat <<EOF > f2
	| cat <<"EOF" > f3 | ls > ls | cat f1 | cat f2 | cat f3 | cat
	ls > ls | cat ls
	2- ls > test1 | cat << test2 << test3 | pwd | pwd | cat <<
	$HOME > test4

				// print_tree_structure(ast);
			// print_tree(ast, 0);
					// print_tokens(tokens, token_count);
*/