/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 01:19:06 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_signal;

static int	handle_heredocs(t_tree_node *ast, t_data *data, t_list_head *n_head)
{
	if (collect_heredocs(ast, data) == -1)
	{
		free_all(n_head);
		n_head->head = NULL;
		return (-1);
	}
	return (0);
}

static void	process_prompt(char *prompt, t_list_head *n_head, t_data *data)
{
	t_token		*tokens;
	t_tree_node	*ast;
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
		if (ast && handle_heredocs(ast, data, n_head) != -1)
			execute_ast(ast, data);
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
