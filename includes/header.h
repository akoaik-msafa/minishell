/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:31:25 by msafa             #+#    #+#             */
/*   Updated: 2025/09/12 00:44:25 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef int	(*t_built_in)(char *arg);

typedef struct s_built_in
{
	char		*cmd;
	t_built_in	func;
}	t_builtin;

/* Builtin functions */
int		ft_echo(char *arg);
int		ft_cd(char *arg);
int		ft_pwd(char *arg);
int		ft_export(char *arg);
int		ft_unset(char *arg);
int		ft_env(char *arg);
int		ft_exit(char *arg);

/* Helper functions */
int		ft_strcmp(const char *s1, const char *s2);
int		count_words(char *str);
void	skip_spaces(char *str, int *i);
char	*extract_word(char *str, int *i);
char	**ft_split(char *str);
void	free_split(char **split);

/* Echo functions */
int		check_options(char *arg);
int		process_echo_options(char **args);
void	print_echo_args(char **args, int start_index);
int		calculate_total_length(char **args);
void	copy_args_to_result(char **args, char *result);
char	*join_args(char **args);

/* CD functions */
char	*get_home_path(void);
int		is_only_spaces(char *str);
char	*extract_from_quotes(char *arg, int start, int end);
int		find_closing_quote(char *arg, int start, char quote);
char	*handle_quoted_path(char *arg, int *i);
char	*extract_quoted_path(char *arg);
char	*get_cd_path(char *arg, char ***args_ptr);
void	print_cwd(const char *label);

/* Main functions */
void	init_builtins(t_builtin *builtins);