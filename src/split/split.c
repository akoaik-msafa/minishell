/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:32:17 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 23:30:53 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data_args(char *cmd_line, data_handle_args *data_args,
		t_list_head *n_head)
{
	data_args->count = count_tokens(cmd_line);
	if (data_args->count == -1)
	{
		printf("Error: unclosed quote\n");
		return (NULL);
	}
	if (data_args->count == 0)
		return (NULL);
	data_args->expand_flags = ft_malloc(data_args->count * sizeof(char),
			n_head);
	if (!data_args->expand_flags)
	{
		data_args->count = 0;
		return (NULL);
	}
}
void find_closed_quote(char *str,char *quote_flag,data_handle_args *data_args)
{
    int i;
    int end;

    i = data_args->start;
    while(str[i] && str[i] != '"')
        i++;
    if(str[i] && str[i] == '"')
    {
        quote_flag = '"';
        data_args->end = data_args->start - 1;
        i++;
        return;
    }
}

char *alloc_tokens(char *cmd_line,data_handle_args *data_args,t_list_head *n_head)
{
    int len;
    char *str;

    len = data_args->end - data_args->start;
    str = ft_malloc((len + 1) * sizeof(char),n_head);
    if(str)
        ft_strlcpy(str,cmd_line + data_args->start,len + 1);
}

char	**extract_tokens(char *cmd_line, data_handle_args *data_args,
		t_list_head *n_head)
{
	char	**arguments;
    char    *quote_flag;
	int		i;
    int     j;

    quote_flag = NULL;
	arguments = ft_malloc((data_args->count + 1) * sizeof(char *), n_head);
	if (!arguments)
		return (NULL);
	arguments[data_args->count] = NULL;
    while(cmd_line[i] && j < data_args->count)
    {
        if(cmd_line[i] == '"' || cmd_line[i] == '\'')
        {
            data_args->start = i + 1;
            find_closed_quote(cmd_line,&quote_flag,data_args);
            arguments[j] = alloc_tokens(cmd_line,data_args,n_head);
        }
    }
}

char	**splite_token(char *cmd_line, data_handle_args *data_args,
		t_list_head *n_head)
{
	char **arguments;

	if (!cmd_line)
		return (NULL);

	init_data_args(cmd_line, &data_args, n_head);
	arguments = extract_tokens(cmd_line, data_args, n_head);
	if (!arguments)
	{
		data_args->count = 0;
		return (NULL);
	}
	return (arguments);
}