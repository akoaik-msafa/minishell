/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:36:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 21:10:51 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "data.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

void		*ft_malloc(size_t size, struct list_head *n_head);
void		free_all(struct list_head *n_head);
char		*get_user_input(void);
tree_node	*creat_node(node_type type, struct list_head *hn);
char		*my_strdup(const char *s1, struct list_head *head);
char		**split_string(const char *str, int *count, struct list_head *n_head);
token_t		*tokenize_input(const char *input, int *count, struct list_head *head);
tree_node	*parse_tokens(token_t *tokens, int count, struct list_head *head);
tree_node	*create_cmd_node(token_t **current, token_t *end, struct list_head *head);
tree_node	*create_pipe_node(tree_node *left, tree_node *right, struct list_head *head);
void		execute_ast(tree_node *ast, t_env *env);
int			init_env(t_env *env, char **envp, struct list_head *head);
char		**get_env(t_env *env);
int			get_env_count(t_env *env);

#endif
