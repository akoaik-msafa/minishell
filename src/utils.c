/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:30:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/10 20:30:00 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

int	ft_exit(char *arg)
{
	if (arg)
		printf("exit command: %s\n", arg);
	else
		printf("exit command: no args\n");
	return (0);
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
