/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:31:25 by msafa             #+#    #+#             */
/*   Updated: 2025/10/27 23:31:31 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "data.h"

// builtins.c
token_type	is_builtin(const char *cmd);

// cd.c
char		*get_home_path(t_env *env);
int			is_only_spaces(char *str);
char		*get_cd_path(char *arg, t_env *env, t_list_head *n_head);
int			ft_cd(char **args, t_env *env, t_list_head *n_head);

// cd_utils.c
int			find_closing_quote(char *arg, int start, char quote);
char		*extract_from_quotes(char *arg, int start, int end,
				t_list_head *n_head);
char		*handle_quoted_path(char *arg, int *i, t_list_head *n_head);
char		*extract_quoted_path(char *arg, t_list_head *n_head, t_env *env);

// pwd.c
int			ft_pwd(char **args);

// echo.c
int			ft_echo(char **args);
char		**echo_split(char *str);

// export.c
int			ft_strcmp(const char *s1, const char *s2);
int			array_len(char **env);
char		**sorted_env(t_env *env, t_list_head *n_head);
int			validate_identifier(char *arg);
int			find_env_var(char *var_name, char **env);
void		append_to_env(char *arg, t_env *env, int index,
				t_list_head *env_head);
void		update_env(char *arg, t_env *env, int index, t_list_head *env_head);
void		add_to_env(char *arg, t_env *env, t_list_head *env_head);
void		add_var_no_value(char *arg, t_env *env, t_list_head *env_head);
int			ft_export(char **args, t_data *data);
void		update_export(char *arg, t_env *env, int index,
				t_list_head *env_head);

// unset.c
int			ft_unset(char **args, t_env *env);

// env.c

int			ft_env(char **arg, t_env *env);

// exit.c
int			ft_exit(char **args, t_data *data);

#endif
