/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:05:20 by msafa             #+#    #+#             */
/*   Updated: 2025/09/03 21:43:02 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		void rl_replace_line(const char *text, int clear_undo);
		clear_undo : 1 to clear undo history & 0 to keep undo history
2. Return value:
		- void ( we just call it to update the internal readline buffer)
3. Definition
		- it replaces the entire current input line (that the user has typed but not yet submitted with Enter).
		- it is used usually to pass an empty string to clear the input buffer 
4. Note that re_replace_line is always paired with rl_on_new_line + rel_redisplay
*/


// here readline will not redraw the screen will just clear the buffer internally
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);   // clear buffer
    rl_on_new_line();
    rl_redisplay();
}

int main(void)
{
    signal(SIGINT, sigint_handler);

    char *input;
    while ((input = readline("minishell> ")) != NULL)
    {
        free(input);
    }
    return 0;
}
