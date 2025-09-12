/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:38:15 by msafa             #+#    #+#             */
/*   Updated: 2025/09/01 21:26:38 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		Char *readline(const cha *prompt)
2. Return value:
		-A pointer to the string the user entered(without the new line\n)
		-NULL if end of file(Ctrl+D) is reached || an error occurs
3. Definition
		- From the Readline library
		- A string called prompt is passed as argument to shows the user that the shell
			is ready to accept input so the user know where to type their command
		- The returned string can be used to print it back or parsing it into commands and arguments
			or adding it to history with add_history that will be explained later on
4. You should free() after done using it because it allocates memory for the string
5. Keeps track of:

	-the current line buffer : the text you've typed so far but not yet submitted(not yet pressed Enter)

	-the cursor position : if you have for example "hello" , if you move the cursor to the first l then the cursor position is there 

	-where the prompt should reappear : readlien has to know that everytime it redisplay it should print the prompt on a new line then draw the buffer
		so if you miss rl_on_new_line readline might be messy
*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    input = readline("minishell> ");  // display prompt and read input
    if (input == NULL)  // user pressed Ctrl+D
        return 0;

    printf("You entered: %s\n", input);

    free(input);  // free allocated memory
    return 0;
}
// cc readline.c -lreadline 
