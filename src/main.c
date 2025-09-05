/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:43:55 by msafa             #+#    #+#             */
/*   Updated: 2025/09/05 23:54:08 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void dis()
{
	// signal(SIGINT, sigint_handler);
	char *input;
    while ((input = readline("minishell> ")) != NULL)
    {
		add_history(input);
        free(input);
    }
}

int main (int argc,char **argv,char ***envp)
{
	dis();
}