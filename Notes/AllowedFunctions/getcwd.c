/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:03:48 by msafa             #+#    #+#             */
/*   Updated: 2025/09/05 00:10:03 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Syntax:
	char *getcwd(char *buf,size_t size);
2. Definition:
	returns the current working directory (absolute path)
- buf is a pointer to a buffer to store the path
- size is the size of the buffer
Note that if buf is NULL, getcwd allocated memory dynamically and create a buffer internally
which is large enough to hold the current path
So this funciton tells you exactly where your shell is currently located in the filesystem

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0); // dynamically allocate buffer
    if (!cwd) {
        perror("getcwd");
        return 1;
    }

    printf("Current directory: %s\n", cwd);
    free(cwd); // free buffer if dynamically allocated

    return 0;
}
/*

another way is to use your own buffer
char buf[path_max];
char *cwd = getcwd(bug,sizeof(buf));

so here no free is needed because the memory is managed by you just we have to make sure
that the buffer is big enough to hold the path
*/