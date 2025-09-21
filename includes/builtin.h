/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:31:25 by msafa             #+#    #+#             */
/*   Updated: 2025/09/20 17:51:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "data.h"

// builtins.c
token_type	is_builtin(const char *cmd);

// cd.c
char	*get_home_path(t_env *env);
int	is_only_spaces(char *str);
char	*get_cd_path(char *arg, char ***args_ptr, t_env *env);
int	ft_cd(char *arg, t_env *env);

// cd_utils.c
int	find_closing_quote(char *arg, int start, char quote);
char	*extract_from_quotes(char *arg, int start, int end);
char	*handle_quoted_path(char *arg, int *i);
char	*extract_quoted_path(char *arg);

#endif
