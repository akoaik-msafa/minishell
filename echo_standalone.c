/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_standalone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:00:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/12 04:00:00 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Structure definitions */
typedef int	(*t_built_in)(char *arg);

typedef struct s_built_in
{
	char		*cmd;
	t_built_in	func;
}	t_builtin;

/* Helper functions from helpers.c */
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
	}
	return (count);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

char	*extract_word(char *str, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t')
		(*i)++;
	len = *i - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	strncpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < word_count)
	{
		skip_spaces(str, &i);
		result[j] = extract_word(str, &i);
		if (!result[j])
			return (NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* Echo-specific functions from echo.c */
int	check_options(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
			if (arg[i] == '\0')
				return (1);
		}
	}
	return (0);
}

int	process_echo_options(char **args)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	while (args[i] && check_options(args[i]))
	{
		option = 1;
		i++;
	}
	return (option);
}

void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	calculate_total_length(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

void	copy_args_to_result(char **args, char *result)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (args[i])
	{
		strcpy(result + pos, args[i]);
		pos += strlen(args[i]);
		if (args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	result[pos] = '\0';
}

char	*join_args(char **args)
{
	int		total_len;
	char	*result;

	if (!args || !args[0])
		return (NULL);
	total_len = calculate_total_length(args);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	copy_args_to_result(args, result);
	return (result);
}

int	ft_echo(char *arg)
{
	char	**args;
	int		option;
	int		start_index;

	if (!arg)
	{
		printf("\n");
		return (0);
	}
	args = ft_split(arg);
	if (!args)
		return (1);
	option = process_echo_options(args);
	start_index = 0;
	while (args[start_index] && check_options(args[start_index]))
		start_index++;
	print_echo_args(args, start_index);
	if (!option)
		printf("\n");
	free_split(args);
	return (0);
}

/* Stub functions for other builtins (not implemented in this standalone version) */
int	ft_cd(char *arg) { (void)arg; return (0); }
int	ft_pwd(char *arg) { (void)arg; return (0); }
int	ft_export(char *arg) { (void)arg; return (0); }
int	ft_unset(char *arg) { (void)arg; return (0); }
int	ft_env(char *arg) { (void)arg; return (0); }
int	ft_exit(char *arg) { (void)arg; return (0); }

/* Main function from main.c */
void	init_builtins(t_builtin *builtins)
{
	builtins[0].cmd = "echo";
	builtins[0].func = ft_echo;
	builtins[1].cmd = "cd";
	builtins[1].func = ft_cd;
	builtins[2].cmd = "pwd";
	builtins[2].func = ft_pwd;
	builtins[3].cmd = "export";
	builtins[3].func = ft_export;
	builtins[4].cmd = "unset";
	builtins[4].func = ft_unset;
	builtins[5].cmd = "env";
	builtins[5].func = ft_env;
	builtins[6].cmd = "exit";
	builtins[6].func = ft_exit;
}

int	main(int argc, char **argv)
{
	t_builtin	builtins[7];
	int			nb_builtins;
	int			i;
	char		*args_str;

	init_builtins(builtins);
	i = 0;
	nb_builtins = 7;
	if (argc < 2)
	{
		printf("Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	while (i < nb_builtins)
	{
		if (ft_strcmp(argv[1], builtins[i].cmd) == 0)
		{
			args_str = join_args(argv + 2);
			(builtins[i].func)(args_str);
			if (args_str)
				free(args_str);
			break ;
		}
		i++;
	}
	return (0);
}