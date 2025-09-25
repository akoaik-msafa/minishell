/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:44:40 by msafa             #+#    #+#             */
/*   Updated: 2025/09/25 18:56:08 by msafa            ###   ########.fr       */
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

static void	handle_char(const char *str, int *i, int *count,
						int *in_quotes, char *quote_char)
{
	int		op_len;

	if (!*in_quotes && (str[*i] == '"' || str[*i] == '\''))
	{
		if (*i == 0 || str[*i - 1] == ' ' || str[*i - 1] == '\t')
			(*count)++;
		*quote_char = str[*i];
		*in_quotes = 1;
	}
	else if (*in_quotes && str[*i] == *quote_char)
		*in_quotes = 0;
	else if (!*in_quotes && (op_len = is_operator(str[*i], str[*i + 1])) > 0)
	{
		(*count)++;
		*i += op_len - 1;
	}
	else if (!*in_quotes && str[*i] != ' ' && str[*i] != '\t')
	{
		if (*i == 0 || str[*i - 1] == ' ' || str[*i - 1] == '\t'
			|| is_operator(str[*i - 1], str[*i]))
			(*count)++;
	}
}

int	count_tokens(const char *str)
{
	int		i;
	int		count;
	int		in_quotes;
	char	quote_char;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i])
	{
		handle_char(str, &i, &count, &in_quotes, &quote_char);
		i++;
	}
	if (in_quotes)
		return (-1);
	return (count);
}
