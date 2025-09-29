/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:14:12 by msafa             #+#    #+#             */
/*   Updated: 2025/09/29 23:14:13 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"

static tree_node *parse_left_side(token_t *tokens, token_t *redir_pos, t_list_head *n_head, t_env *env)
{
    int cmd_count;

    cmd_count = redir_pos - tokens;

    if (cmd_count > 0)
    {
        return parse_tokens(tokens, cmd_count, n_head, env);
    }
    return NULL;
}

static tree_node *parse_right_side(token_t *redir_pos, token_t *end, t_list_head *n_head, t_env *env)
{
    int remaining_count;
    token_t *remaining_start;

    remaining_start = redir_pos + 2;
    remaining_count = end - remaining_start;

    if (remaining_count > 0)
    {
        return parse_tokens(remaining_start, remaining_count, n_head, env);
    }
    return NULL;
}

tree_node *new_handle_redirection_parsing(token_t *tokens, token_t *redir_pos, token_t *end, t_list_head *n_head, t_env *env)
{
    tree_node *left_node;
    tree_node *right_node;
    tree_node *result_node;
    char *filename;

    if (redir_pos + 1 >= end || (redir_pos + 1)->type != t_word)
    {
        return NULL;
    }

    filename = (redir_pos + 1)->str;
    left_node = parse_left_side(tokens, redir_pos, n_head, env);
    right_node = parse_right_side(redir_pos, end, n_head, env);

    if (right_node && right_node->type == redir_node)
    {
        tree_node *temp_rihgt_node = right_node;
        while (temp_rihgt_node->left && temp_rihgt_node->left->type == redir_node) // going throw the all left nodes till we rech a empty one --> replace it with the new left node
            temp_rihgt_node = temp_rihgt_node->left;

        if (!temp_rihgt_node->left)
            temp_rihgt_node->left = left_node; // the replacment

        result_node = create_redir_node(redir_pos->type, filename, right_node, n_head, (redir_pos + 1)->expand_flag);
    }
    else
    {
        result_node = create_redir_node(redir_pos->type, filename, left_node, n_head, (redir_pos + 1)->expand_flag);
    }

    return result_node;
}
