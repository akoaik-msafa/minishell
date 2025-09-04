/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:57:33 by msafa             #+#    #+#             */
/*   Updated: 2025/09/03 22:07:42 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax : 
		void add_history(const char *line);
2. Return value:
		None(void)
3. Definition
		- adds a line of text to the readline history list because it does not
			automatically add input to history
		- As in Bash, zsh after we use a command and press Enter we can press up and down 
			to get the previous inputs so simply it make the use inputs available via arrow keys
*/