/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:32:17 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/09 23:30:53 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static token_type	identify_token_type(const char *str)
{
	if (!str)
		return (t_eof);
	if (ft_strncmp(str, "|", 1) == 0 && ft_strlen(str) == 1)
		return (t_pipe);
	if (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		return (t_re_heredoc);
	if (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2)
		return (t_re_append);
	if (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		return (t_re_in);
	if (ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		return (t_re_out);
	return (t_word);
}

static char	**splite_token(const char *prompt, int *count,
		struct list_head *head)
{
	char	**words;
	int		cnt;

	words = split_string(prompt, &cnt, head);
	if (!words)
		return (NULL);
	*count = cnt;
	return (words);
}

static void	fill_tokens_array(token_t *tokens, char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		tokens[i].str = strs[i];
		tokens[i].type = identify_token_type(strs[i]);
		i++;
	}
	tokens[count].type = t_eof;
	tokens[count].str = NULL;
}

token_t	*tokenize_input(const char *prompt, int *count, struct list_head *head)
{
	char	**strs;
	token_t	*tokens;
	int		cnt;

	if (!prompt || !count)
		return (NULL);
	strs = splite_token(prompt, &cnt, head);
	if (!strs)
		return (NULL);
	tokens = ft_malloc((cnt + 1) * sizeof(token_t), head);
	if (!tokens)
		return (NULL);
	fill_tokens_array(tokens, strs, cnt);
	*count = cnt;
	return (tokens);
}
