/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_clear_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:18:01 by msafa             #+#    #+#             */
/*   Updated: 2025/08/31 21:31:06 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		void rl_clear_history(void);
2. Return value:
		None(void)
3. Definition
		- From the Readline library
		- Clears all previously stored command history in the current session
		- After calling it ,up/down arrows will not recall any past commands

*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while ((input = readline("minishell> ")) != NULL)
    {
        if (*input)  // add non-empty lines to history
            add_history(input);

        printf("You typed: %s\n", input);

        free(input);
		printf("Clearing history...\n");
    	rl_clear_history();  // remove all saved commands
    }
	// try to add the function here and see the difference :)
    return 0;
}
