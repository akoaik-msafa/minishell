/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:53:09 by msafa             #+#    #+#             */
/*   Updated: 2025/09/25 18:28:30 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void data_init(data_handle_args *data_args)
{
    data_args->count = 0;
	data_args->expand_flags = NULL;
}

token_t *tokenize_input(char *cmd_line, t_list_head *n_head)
{
    token_t *tokens_arr;
    char **arguments;
    data_handle_args data_args ;

    data_init(&data_args);
    arguments = splite_token(cmd_line, &data_args, n_head);
    if (!arguments)
        return (NULL);
    fill_token_array();
    // return 
}