/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:22:28 by msafa             #+#    #+#             */
/*   Updated: 2025/09/19 03:27:13 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int here_doc(char *delimiter)
{
    char *temp_file = "/tmp/heredoc_tmp";
    int fd_write;
    int fd_read;
    char *line;

    fd_write = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if(fd_write == -1)
        return(-1);
    while(1)
    {
        line = readline("heredoc>");
        if(!line)
            break;
        if((delimiter && ft_strcmp(line,delimiter) == 0) || (!delimiter && line[0] == '\0'))
        {
            free(line);
            break;
        }
        write(fd_write,line,ft_strlen(line));
        write(fd_write,"\n",1);
        free(line);
    }
    close(fd_write);
    fd_read = open(temp_file,O_RDONLY);
    if(fd_read == -1)
        return(-1);
    unlink(temp_file);
    return(fd_read);
}

int redirect_append(char *filename)
{
    int fd_append;
    
    fd_append = open(filename,O_WRONLY | O_APPEND | O_CREAT,0644);
    if(fd_append == -1)
    {
        perror("minishell");
        return(-1);
    }
    return(fd_append);
}