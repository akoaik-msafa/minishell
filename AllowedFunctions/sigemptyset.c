/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigemptyset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:48:30 by msafa             #+#    #+#             */
/*   Updated: 2025/09/04 23:52:21 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. Syntax:
	int sigemptyset(sigset_t *set);
2. Definition:
	sigset_t is a type used to represent a set of signals. You can block, unblock
		or test signals using these sets
	so sigemtpyset initialize a signal set to be empty
*/

struct sigaction sa;
sigemptyset(&sa.sa_mask); //start with an empty set

//so here the handler won't block any signals unless you explicitly add them with sigaddset()
