/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:38:11 by akoaik            #+#    #+#             */
/*   Updated: 2025/08/31 21:37:18 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	readdir() : Function that reads the next
	entry (file, folder) from a open Folder
*/

/* ------ same example of opendir ------ */ 
#include <stdio.h>
#include <dirent.h>

int main (void)
{
	DIR *folder ;

	folder = opendir("."); /*
						or any path */
	if (folder == NULL)
	{
		perror("opendir");
		return (1);
	}

	struct dirent *entry;   /*
	--> dirent is a structure that describes one 
		entry (one file or folder) inside a directory.*/

	// Read the first file/folder inside the directory
	entry = readdir(folder); 

	// Loop through all entries until readdir returns NULL (no more files)
	while(entry != NULL)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(folder);
	}

	// Close the directory when done.
	closedir(folder);
}
/*
	In a minishell, readdir is used to get one file or folder at a time from an open
	directory, allowing commands like ls to list all directory contents.
*/