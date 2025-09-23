/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:15:33 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/23 14:00:05 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

// holding the env copied
typedef struct s_env
{
	char				**envp;
	char				**export_only;
	int					count;
}						t_env;

// AGC struct
struct					alloc_list
{
	void				*allocation;
	struct alloc_list	*next;
};

// AGC head holder
typedef struct			list_head
{
	struct alloc_list	*head;
}						t_list_head;

// enumeration for types of token
typedef enum
{
	t_word,
    t_builtin,
    t_env_builtin,
	t_pipe,
	t_re_in,
	t_re_out,
	t_re_append,
	t_re_heredoc,
	t_eof
}						token_type;

// each part is :
typedef struct
{
	token_type			type;
	char				*str;
	int					expand_flag;
}						token_t;

// token send position for 1 function
typedef struct data_handle_args
{
	token_t			*tokens;
	token_t			*pipe_position;
	token_t			*end;
	int				count;
	char			*expand_flags;
}					data_handle_args;

// enum to indecate the type inside the tree node
typedef enum
{
	cmd_node,
	pipe_node,
	redir_node
}						node_type;



// tree_node (each node compose of :
typedef struct tree_node
{
	node_type			type;
	char				**args;
	char				*filename;
	token_type			redir_type;
	struct tree_node	*left;
	struct tree_node	*right;
}						tree_node;



#endif