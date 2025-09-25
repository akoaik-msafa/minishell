/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:36:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/25 18:48:09 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "builtin.h"
# include "data.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char		*get_user_input(void);
void		temp_exit(char *str, t_list_head *n_head, t_list_head *env_head);
void		*ft_malloc(size_t size, t_list_head *n_head);
void		free_all(t_list_head *n_head);
token_t		*tokenize_input(const char *prompt, int *token_count,
				t_list_head *n_head);
tree_node	*create_pipe_node(tree_node *left, tree_node *right,
				t_list_head *n_head);
tree_node	*create_cmd_node(token_t **current, token_t *end,
				t_list_head *n_head, t_env *env);
tree_node	*create_redir_node(token_type redir_type, char *filename,
				tree_node *cmd, t_list_head *n_head);
char		*expand_variable(const char *str, t_env *env,
				struct list_head *head);
char		*my_strdup(const char *s1, struct list_head *n_head);
char		**get_env(t_env *env);
tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head,
				t_env *env);
int			init_env(t_env *env, char **envp, t_list_head *head);
void		execute_ast(tree_node *ast, t_env *env, t_list_head *n_head,t_list_head *env_head);
char		**split_string(const char *str, data_handle_args *data_args,
				t_list_head *n_head);
char		*join_args(char **args);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);

// path_utils.c
void		free_split(char **strs);
char		*find_path_env(t_env *env);
char		*build_full_path(char *dir, char *cmd);
char		*search_in_paths(char **paths, char *cmd);
char		*get_cmd_path(char *cmd, t_env *env);
int	count_tokens(const char *str);

// command_exec.c
void		exec_cmd(tree_node *node, t_env *env);
int			execute_builtin(tree_node *node, t_env *env, t_list_head *n_head,t_list_head *env_head);
void		execute_command(tree_node *node, t_env *env, t_list_head *n_head,t_list_head *env_head);

// pipe_exec.c
int			child1(tree_node *cmd_node, int *pipefd, t_env *env, t_list_head *n_head, t_list_head *env_head);
int			child2(tree_node *cmd_node, int *pipefd, t_env *env, t_list_head *n_head, t_list_head *env_head);
void		execute_pipe(tree_node *ast, t_env *env, t_list_head *n_head,t_list_head *env_head);

// Printing.c
void		print_2d(char **arr);
void		print_tokens(token_t *tokens, int count);
void		print_ast(tree_node *node, int depth);
void		print_tree_structure(tree_node *ast);

// redirections.c
int			here_doc(char *delimiter);
int			redirect_append(char *filename);
void		handle_heredoc_redirection(tree_node *ast, t_env *env, t_list_head *n_head, t_list_head *env_head);

#endif
