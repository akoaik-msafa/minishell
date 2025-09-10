/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:31:25 by msafa             #+#    #+#             */
/*   Updated: 2025/09/10 22:52:19 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef int	(*t_built_in)(char **args);

typedef struct s_built_in
{
	char		*cmd;
	t_built_in	func;
}	t_builtin;

int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(char **args);
int		ft_export(char **args);
int		ft_unset(char **args);
int		ft_env(char **args);
int		ft_exit(char **args);
int		ft_strcmp(const char *s1, const char *s2);
int		check_options(char *arg);
void	init_builtins(t_builtin *builtins);