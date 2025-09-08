/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:15:33 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/08 19:53:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef DATA_H
# define DATA_H

struct list_head {
	struct alloc_list *head ;
};

struct alloc_list
{
    void *allocation;
    struct alloc_list *next;
};

typedef enum {
	t_word,
	t_pipe,
	t_re_in,
	t_re_out,
	t_re_append,
	t_re_heredoc,
	t_eof
} token_type ;

typedef enum {
	node_cmd,
	node_pipe,
	node_redirect
} node_type ;

typedef struct {
	token_type type ;
	char *value;
} token_t ;

typedef struct tree_node {
	node_type type ;
	char **args;
	struct tree_node *left ;
	struct tree_node *rigt ;
	char *filename;
	token_type redir_type ;
} tree_node ;

#endif