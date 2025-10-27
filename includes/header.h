/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:36:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 23:31:38 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "builtin.h"
# include "data.h"
# include "gv.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

char		*get_user_input(void);
char		*copy_env(char *src, t_list_head *head);
int			array_len(char **env);
int			validate_identifier(char *arg);
int			find_env_var(char *var_name, char **env);
void		update_export(char *arg, t_env *env, int index,
				t_list_head *env_head);
void		update_env(char *arg, t_env *env, int index, t_list_head *env_head);
void		temp_exit(char *str, t_list_head *n_head, t_list_head *env_head);
void		*ft_malloc(size_t size, t_list_head *n_head);
void		free_all(t_list_head *n_head);
void		init_data(t_data *data, t_list_head *n_head, t_env *env,
				t_list_head *env_head);
token_t		*tokenize_input(char *cmd_line, t_data *data);
t_tree_node	*create_pipe_node(t_tree_node *left, t_tree_node *right,
				t_list_head *n_head);
t_tree_node	*create_cmd_node(token_t **current, token_t *end,
				t_list_head *n_head, t_data *data);
t_tree_node	*create_redir_node(token_t *redir_pos, t_tree_node *cmd,
				t_data *data);
char		*expand_variable(const char *str, t_data *data);
char		*remove_escape_dollar(const char *str, t_data *data);
int			has_unescaped_dollar(const char *str);
char		*my_strdup(const char *s1, struct list_head *n_head);
char		*my_strjoin(char const *s1, char const *s2, t_list_head *n_head);
char		*my_ft_strtrim(char const *s1, char const *set,
				t_list_head *n_head);
char		**get_env(t_env *env);
void		add_to_export_only(char *arg, t_env *env, t_list_head *env_head);
char		*ft_itoa_with_head(int n, t_list_head *head);
int			init_envp_array(t_env *env, char **envp, t_list_head *head);
int			init_export_array(t_env *env, t_list_head *head);
char		*create_shlvl_entry(char *new_shlvl_str, t_list_head *head);
void		update_shlvl_entries(t_env *env, int export_index,
				char *new_shlvl_str, t_list_head *head);
void		handle_shlvl_init(t_env *env, t_list_head *head);
t_tree_node	*parse_tokens(token_t *tokens, int count, t_list_head *n_head,
				t_data *data);
t_tree_node	*handle_redirection_parsing(token_t *tokens, token_t *redir_pos,
				token_t *end, t_data *data);
token_t		*find_redirection(token_t *current, token_t *end);
char		**merge_args(t_tree_node *left_node, t_tree_node *right_node,
				t_list_head *n_head);
t_tree_node	*handle_cmd_node_case(t_tree_node *left_node, t_tree_node *right_node,
				token_t *redir_pos, t_data *data);
t_tree_node	*handle_default_case(t_tree_node *left_node, t_tree_node *right_node,
				token_t *redir_pos, t_data *data);
int			init_env(t_env *env, char **envp, t_list_head *head);
void		execute_ast(t_tree_node *ast, t_data *data);
char		**split_string(const char *str, data_handle_args *data_args,
				t_list_head *n_head);
void		fill_tokens_array(token_t *tokens, char **strs,
				data_handle_args *data_args);
token_type	is_builtin(const char *cmd);
token_type	identify_token_type(const char *str);
char		**splite_token(char *cmd_line, data_handle_args *data_args,
				t_data *data);
int			count_token_array(token_t *tokens);
char		*join_args(char **args);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
void		init_sigaction(struct sigaction *signals);

// path_utils.c
void		free_split(char **strs);
char		*find_path_env(t_env *env);
char		*build_full_path(char *dir, char *cmd);
char		*search_in_paths(char **paths, char *cmd);
char		*get_cmd_path(char *cmd, t_env *env);
int			count_tokens(const char *str);
int			count_refactored(const char *str);
int			is_operator(char c1, char c2);
int			is_whitespace(char c);
int			is_opening_quote(char c, t_token_state *state);
int			is_closing_quote(char c, t_token_state *state);
int			is_operator_char(const char *str, int i, t_token_state *state);
int			is_whitespace_char(char c, t_token_state *state);
int			is_regular_char(char c, t_token_state *state);
void		handle_quote_start(int *count, t_token_state *state, char c);
void		handle_operator(const char *str, int *i, int *count,
				t_token_state *state);
void		handle_whitespace(t_token_state *state);
void		handle_regular_char(int *count, t_token_state *state);
int			process_string(const char *str, int *count);
int			find_closed_quote(char *str, int start, char *quote_flag);
char		*alloc_tokens(char *cmd_line, data_handle_args *data_args,
				t_list_head *n_head);
int			extract_complete_word(char *cmd_line, data_handle_args *data_args,
				char **result, t_data *data);

// extract_word_utils.c
int			count_quoted_length(char *cmd_line, int i, char quote_flag,
				int end_quote);
int			is_word_delimiter(char c);

// command_exec.c
void		exec_cmd(t_tree_node *node, t_env *env);
int			execute_builtin(t_tree_node *node, t_data *data);
void		execute_command(t_tree_node *node, t_data *data);

// cmd_validation.c
void		handle_cmd_not_found(char *cmd_name);
int			validate_cmd_path(char *cmd_path);

// builtin_exec.c (already declared above in command_exec.c)

// cmd_fork.c
void		fork_and_execute(t_tree_node *node, t_data *data);

// expand_helpers.c
int			get_var_name_length(const char *var_name);
char		*find_env_value(const char *var_name, int var_len, t_env *env);
char		*build_result(char *prefix, char *var_value, char *suffix,
				t_data *data);
int			find_dollar_position(const char *str);
char		*handle_whitespace_after_dollar(const char *str, int j,
				t_data *data);

// expand_helpers2.c
char		*remove_backslash_escapes(const char *str, t_data *data);

// exit_code.c
void		set_exit_code_from_status(t_data *data, int status);

// pipe_exec.c
int			child1(t_tree_node *cmd_node, int *pipefd, t_data *data);
int			child2(t_tree_node *cmd_node, int *pipefd, t_data *data);
void		execute_pipe(t_tree_node *ast, t_data *data);
int			collect_heredocs(t_tree_node *node, t_data *data);

// pipe_exec_utils.c
int			process_heredoc_node(t_tree_node *node, t_data *data);
int			process_pipe_node(t_tree_node *node, t_data *data);

// Printing.c
void		print_2d(char **arr);
void		print_tokens(token_t *tokens, int count);
void		print_ast(t_tree_node *node, int depth);
void		print_tree_structure(t_tree_node *ast);
void		print_tree(t_tree_node *node, int depth);

// redirections.c
int			here_doc(char *delimiter, t_data *data, int expand_flag);
int			redirect_append(char *filename, t_data *data);
void		handle_heredoc_redirection(t_tree_node *ast, t_data *data);
int			handle_append_redirection(t_tree_node *ast, t_data *data);
int			handle_redirection_input(t_tree_node *ast, t_data *data);

// heredoc_utils.c
int			check_heredoc_status(int status, t_data *data);
int			open_heredoc_file(char *temp_file, int saved_stdin);

int			handle_output_redirection(t_tree_node *ast, t_data *data);

// sort.c
char		**bubble_sorting(char **str, t_env *env);
char		**sorted_env(t_env *env, t_list_head *n_head);

// export_handle.c
void		print_sorted(char **sorted);
void		handle_existing_var(char *arg, int index_env, int index_export,
				t_data *data);
void		handle_new_var(char *arg, t_env *env, t_list_head *env_head);

// add_append_env.c
void		append_to_env(char *arg, t_env *env, int index,
				t_list_head *env_head);
void		add_to_env(char *arg, t_env *env, t_list_head *env_head);

#endif
