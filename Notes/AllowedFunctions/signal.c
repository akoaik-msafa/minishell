/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:33:24 by msafa             #+#    #+#             */
/*   Updated: 2025/09/04 23:28:59 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A SIGNAL is an asynchronous notification sent to a process to tell it that some
// event has occurred
/*

1. Syntax : 
		void (*signal(int signum, void(*handler)(int)))(int);
	- where signum is the signal you want to catch as defined below
	- handler is a function you write that takes an int (the signal number)
2. Return value:
	- a pointer to the previous handler or SIG_ERR if it fails
2. Definition
	-SIGINT (Ctrl-C in terminal -> interrupt)
	-SIGQUIT (Ctrl-\ in terminal -> quit)
	-SIGTERM (Request to terminate)
	-SIGCHILD(Child process ended)
Signal tells the kernel that whenever your process recieves signal X, instead of doing
	the default action, call my function handler
*/

