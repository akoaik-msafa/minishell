/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/21 23:07:19 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
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
	ft_strncpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

char	**echo_split(char *str)
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


int	calculate_total_length(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += ft_strlen(args[i]);
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
		ft_strcpy(result + pos, args[i]);
		pos += ft_strlen(args[i]);
		if (args[i + 1])
			result[pos++] = ' ';
		i++;
	}
	result[pos] = '\0';
}

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
	args = echo_split(arg);
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
