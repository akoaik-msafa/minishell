/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:02:05 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/10 14:48:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void temp_exit (char *str)
{
	if (!ft_strncmp(str, "exit", 4))
		{
			exit(1);
		}
}

void print_2d(char **arr)
{
    int i = 0;
    while (arr && arr[i])
    {
        printf("%s\n", arr[i]);
        i++;
    }
}

void print_tokens(token_t *tokens, int count)
{
    const char *type_names[] = {
        "WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
        "REDIR_APPEND", "REDIR_HEREDOC", "EOF"
    };
    int i = 0;
    
    while (i < count)
    {
        printf("Token %d: '%s' -> %s\n", i, tokens[i].str, type_names[tokens[i].type]);
        i++;
    }
}

int	main(void)
{
	struct list_head	n_head;
	char				*prompt;

	n_head.head = NULL;
	while (1)
	{
		token_t *tokens;
		int token_count;
		
		prompt = get_user_input();
		if (!prompt)
			break;
		printf("Input: '%s'\n", prompt);
		temp_exit(prompt);
		
		tokens = tokenize_input(prompt, &token_count, &n_head);
		printf("Tokenized result (%d tokens):\n", token_count);
		print_tokens(tokens, token_count);
		printf("---\n");
	}
	
}
