/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaddset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:52:47 by msafa             #+#    #+#             */
/*   Updated: 2025/09/05 00:00:58 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. Syntax:
	int sigaddset(sigset_t *set,int signo);
2. Definition;
	- Add a specific signal(signo) to a signal set
	- used together with siemptyset() to build a set of signals you want to block
		while a handler runs
	- so when using sigaction you can temporarily block other signals while handling one

	*/

struct sigaction sa;
sigemptyset(&sa.sa_mask);       // start empty
sigaddset(&sa.sa_mask, SIGQUIT); // block SIGQUIT while handler runs
sa.sa_handler = handler;
sa.sa_flags = 0;
sigaction(SIGINT, &sa, NULL);
