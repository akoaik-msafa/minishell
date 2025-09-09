/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:13:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 18:39:04 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *get_user_input()
{
    char *input = readline("--minishell#-> ");
    if (input && *input != '\0') {
        add_history(input);
    }
    return input;
}
