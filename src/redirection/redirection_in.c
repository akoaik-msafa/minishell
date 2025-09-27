/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/26 00:00:00 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int handle_output_redirection(tree_node *ast, t_env *env, t_list_head *n_head, t_list_head *env_head)
{
    int outfile;
    int saved_fd;

    saved_fd = dup(STDOUT_FILENO);

    outfile = open(ast->filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);

    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    if (ast->left)
        execute_ast(ast->left, env, n_head, env_head);
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    (void)n_head;
    (void)env_head;
    return (0);
}
