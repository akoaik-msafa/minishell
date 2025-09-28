/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:23:45 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/28 16:23:48 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int handle_output_redirection(tree_node *ast, t_data *data)
{
    int outfile;
    int saved_fd;

    saved_fd = dup(STDOUT_FILENO);

    outfile = open(ast->filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);

    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    if (ast->left)
        execute_ast(ast->left, data);
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    return (0);
}

int redirect_append(char *filename)
{
    int outfile;
    int saved_fd;

    saved_fd = dup(STDOUT_FILENO);
    outfile = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
    if (outfile == -1)
    {
        perror("open");
        return (-1);
    }
    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    return (saved_fd);
}

int handle_append_redirection(tree_node *ast, t_data *data)
{
    int saved_fd;

    saved_fd = redirect_append(ast->filename);
    if (saved_fd == -1)
        return (-1);
    if (ast->left)
        execute_ast(ast->left, data);
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    return (0);
}

int handle_redirection_input(tree_node *ast, t_data *data)
{
    int infile;
    int saved_fd;

    saved_fd = dup(STDIN_FILENO);
    infile = open(ast->filename, O_RDONLY);
    if (infile == -1)
    {
        perror("open");
        return (-1);
    }
    dup2(infile, STDIN_FILENO);
    close(infile);
    if (ast->left)
        execute_ast(ast->left, data);
    dup2(saved_fd, STDIN_FILENO);
    close(saved_fd);
    return (0);
}
