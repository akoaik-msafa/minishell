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

typedef int	(*t_simple_func)(char *arg);
typedef int	(*t_env_func)(char *arg, char **env);

typedef struct s_simple_builtin
{
	char		*cmd;
	t_simple_func	func;
}	t_simple_builtin;

typedef struct s_env_builtin
{
	char		*cmd;
	t_env_func	func;
}	t_env_builtin;

/* Builtin functions */
int		ft_echo(char *arg);
int		ft_cd(char *arg);
int		ft_pwd(char *arg);
int		ft_export(char *arg, char ***env);
int		ft_unset(char *arg, char **env);
int		ft_env(char *arg, char **env);
int		ft_exit(char *arg, char **env);

/* Helper functions */
char	*ft_strncpy(char *dest, const char *src, int n);
char	*ft_strdup(const char *s);
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
void	init_simple_builtins(t_simple_builtin *simple_builtins);
void	init_env_builtins(t_env_builtin *env_builtins);
int		search_simple_builtins(char *cmd, char *args_str, t_simple_builtin *simple_builtins);
int		search_env_builtins(char *cmd, char *args_str,
			t_env_builtin *env_builtins, char ***env);
int		execute_builtin(char *input, char ***env);
char	**duplicate_env(char **env);
void	free_env(char **env);