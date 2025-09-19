/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:36:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/18 01:55:44 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

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
tree_node	*create_cmd_node(token_t **current, token_t *end, t_list_head *n_head, t_env *env);
char	*expand_variable(const char *str, t_env *env, struct list_head *head);
char	*my_strdup(const char *s1, struct list_head *n_head);
char	**get_env(t_env *env);
tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head, t_env *env);
int	init_env(t_env *env, char **envp, t_list_head *head);
void	execute_ast(tree_node *ast, t_env *env);
char	**split_string(const char *str, int *count, t_list_head *n_head);

// path_utils.c
void	free_split(char **strs);
char	*find_path_env(t_env *env);
char	*build_full_path(char *dir, char *cmd);
char	*search_in_paths(char **paths, char *cmd);
char	*get_cmd_path(char *cmd, t_env *env);

// command_exec.c
void	exec_cmd(tree_node *node, t_env *env);
void	execute_command(tree_node *node, t_env *env);

// pipe_exec.c
int		child1(tree_node *cmd_node, int *pipefd, t_env *env);
int		child2(tree_node *cmd_node, int *pipefd, t_env *env);
void	execute_pipe(tree_node *ast, t_env *env);

#endif
