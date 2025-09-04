/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_redisplay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:44:14 by msafa             #+#    #+#             */
/*   Updated: 2025/09/03 21:57:11 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		void rl_redisplay(void);
2. Return value:
		None(void)
3. Definition
		- Readline updates the screen automatically as the user types but in special
			cases like signals we should use rl_redisplay along with readline to redraw
			prompt after passing over a fresh line using rl_on_new_line
		- Another special case is if program prints suddnly while the user is typing maybe
			from another process and the input get splitted, this wil not affect the fact that
			readline still has the buffer correct but what we see on the screen is broken
*/