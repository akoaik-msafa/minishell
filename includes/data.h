/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:15:33 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 23:34:16 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_token_state
{
	int					in_quotes;
	int					in_word;
	char				quote_char;
}						t_token_state;

// holding the env copied
typedef struct s_env
{
	char				**envp;
	char				**export_only;
	int					count;
}						t_env;

// AGC struct
struct					s_alloc_list
{
	void				*allocation;
	struct s_alloc_list	*next;
};

// AGC head holder
typedef struct s_list_head
{
	struct s_alloc_list	*head;
}						t_list_head;

// enumeration for types of token
typedef enum s_token_type
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
}						t_token_type;

// each part is :
typedef struct s_token
{
	t_token_type		type;
	char				*str;
	int					expand_flag;
}						t_token;

// token send position for 1 function
typedef struct s_data_handle_args
{
	t_token				*tokens;
	t_token				*pipe_position;
	t_token				*end;
	int					count;
	int					start;
	int					end_index;
	char				*expansion;
	char				*delimiter;
	int					token_index;
	int					is_delimiter;
}						t_data_handle_args;

// enum to indecate the type inside the tree node
typedef enum s_node_type
{
	cmd_node,
	pipe_node,
	redir_node
}						t_node_type;

// t_tree_node (each node compose of :
typedef struct s_tree_node
{
	t_node_type			type;
	char				**args;
	char				*expansion;
	char				*filename;
	t_token_type		redir_type;
	int					heredoc_fd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

// data struct to hold commonly passed variables
typedef struct s_data
{
	t_list_head			*n_head;
	t_env				*env;
	t_list_head			*env_head;
	int					current_expand_flag;
	int					exit_code;
}						t_data;

#endif