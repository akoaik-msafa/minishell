/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:43:41 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/25 22:44:04 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void find_closed_quote(char *str, char *quote_flag, data_handle_args *data_args)
{
    int i;
    char quote_char;

    i = data_args->start;
    if (!str[i] || (str[i] != '"' && str[i] != '\''))
        return;

    quote_char = str[i];
    *quote_flag = quote_char;
    i++;

    while (str[i] && str[i] != quote_char)
        i++;

    if (str[i] == quote_char)
        data_args->end_index = i;
    else
        data_args->end_index = -1;
}

char *alloc_tokens(char *cmd_line,data_handle_args *data_args,t_list_head *n_head)
{
    int len;
    char *str;

    len = data_args->end_index - data_args->start;
    str = ft_malloc((len + 1) * sizeof(char),n_head);
    if(str)
        ft_strlcpy(str,cmd_line + data_args->start,len + 1);
    return (str);
}