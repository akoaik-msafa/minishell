/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:44:40 by msafa             #+#    #+#             */
/*   Updated: 2025/09/26 01:21:56 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_operator(char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
		return (2);
	if (c1 == '>' && c2 == '>')
		return (2);
	if (c1 == '|' || c1 == '<' || c1 == '>')
		return (1);
	return (0);
}

static void	handle_quote_start(int *count, int *in_word, int *in_quotes, 
					char *quote_char, char c)
{
	if (!*in_word)
	{
		(*count)++;
		*in_word = 1;
	}
	*quote_char = c;
	*in_quotes = 1;
}

static void	handle_operator(const char *str, int *i, int *count, int *in_word)
{
	int	op_len;

	*in_word = 0;
	(*count)++;
	op_len = is_operator(str[*i], str[*i + 1]);
	*i += op_len - 1;
}

static void	handle_char(const char *str, int *i, int *count,
						int *in_quotes, char *quote_char, int *in_word)
{
	int		op_len;

	if (!*in_quotes && (str[*i] == '"' || str[*i] == '\''))
		handle_quote_start(count, in_word, in_quotes, quote_char, str[*i]);
	else if (*in_quotes && str[*i] == *quote_char)
		*in_quotes = 0;
	else if (!*in_quotes && (op_len = is_operator(str[*i], str[*i + 1])) > 0)
		handle_operator(str, i, count, in_word);
	else if (!*in_quotes && (str[*i] == ' ' || str[*i] == '\t'))
		*in_word = 0;
	else if (!*in_quotes && str[*i] != ' ' && str[*i] != '\t')
	{
		if (!*in_word)
		{
			(*count)++;
			*in_word = 1;
		}
	}
}

int	count_tokens(const char *str)
{
	int		i;
	int		count;
	int		in_quotes;
	int		in_word;
	char	quote_char;

	i = 0;
	count = 0;
	in_quotes = 0;
	in_word = 0;
	while (str[i])
	{
		handle_char(str, &i, &count, &in_quotes, &quote_char, &in_word);
		i++;
	}
	if (in_quotes)
		return (-1);
	return (count);
}
