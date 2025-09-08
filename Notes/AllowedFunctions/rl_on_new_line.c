/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_on_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:31:34 by msafa             #+#    #+#             */
/*   Updated: 2025/09/01 22:03:33 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		int rl_on_new_line(void)
2. Return value:
		- 0 on success
		- non-zero on error
3. Definition
		- From the Readline library
		- Tells Readline that the cursor is now on a new line
        - it keeps readline’s internal cursor state consistent with what the user actually sees on the terminal.

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void    sigint_handler(int sig)
{
    (void)sig;
    printf("\nCaught SIGINT!\n");

    // If you comment out the 2 lines below, you'll see the messy prompt
    rl_on_new_line();      // tell readline: cursor is now on a fresh line
    rl_replace_line("", 0); // clear the current buffer
    rl_redisplay();        // redraw the prompt properly
}

int main(void)
{
    char *input;

    // set custom handler for Ctrl+C
    signal(SIGINT, sigint_handler);

    while ((input = readline("minishell> ")) != NULL)
    {
        if (*input)
            add_history(input);

        printf("You typed: %s\n", input);
        free(input);
    }

    printf("\nExiting.\n");
    return 0;
}


