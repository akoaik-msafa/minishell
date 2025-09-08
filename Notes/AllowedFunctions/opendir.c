/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:12:21 by akoaik            #+#    #+#             */
/*   Updated: 2025/08/31 20:39:40 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  

	opendir() is a function that allow us to open a
	Directory stream.
	it allows us to read the content of a directory
	(file name inside it)
	
*/

#include <stdio.h>
#include <dirent.h>

int main (void)
{
	DIR *folder ;    /*
		--> DIR is a typedef, it represent a open folder */

	folder = opendir("/home/akoaik/Desktop");
	if (folder == NULL)
	{
		perror("opendir");
		return (1);
	}
}

/*
	In a minishell, we often need to implement commands like ls 
	to list files and directories.
	To do this, the program must read the contents of a directory.
*/