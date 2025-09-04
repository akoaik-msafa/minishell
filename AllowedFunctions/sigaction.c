/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:29:45 by msafa             #+#    #+#             */
/*   Updated: 2025/09/04 23:47:43 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1.Syntax:
	int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact);
-Signum  :which signal you want to handle
-act : new action to take when the signal happens
-oldact : if not NULL, stores the old action(so you can restore it later)

2. Return value:
0 on success & -1 on error

3. Definition and purpose:
Sigaction lets you define exactly what happens when a signal is received so you can provide
a handler function or set options or bloc other signals while handling one

In minishell we have parent and child processes, the parent is waiting for input
so using signal might work but on some systems might not so sigation is more used to 
ensre eveyrthing works smoothly and for the child when run ls for example we usually reset
signals to default and sigaciton if more explicit for this
So signal only set the handler but sigaciton has full control and can use :
1- mask : block signals during handling
2 -flags
3- SA_RESTART : restart syscalls
3- sa_sigaction : extra info about signal
*/

