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

token_type is_builtin(const char *cmd)
{
	if (!cmd)
		return (t_word);
	if (strcmp(cmd, "echo") == 0)
		return (t_builtin);
	if (strcmp(cmd, "cd") == 0)
		return (t_builtin);
	if (strcmp(cmd, "pwd") == 0)
		return (t_builtin);
	if (strcmp(cmd, "export") == 0)
		return (t_env_builtin);
	if (strcmp(cmd, "unset") == 0)
		return (t_env_builtin);
	if (strcmp(cmd, "env") == 0)
		return (t_env_builtin);
	if (strcmp(cmd, "exit") == 0)
		return (t_builtin);
	return (t_word);
}

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
    return (is_builtin(str));
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

static char	**splite_token(const char *prompt, int *counter,
		t_list_head *n_head)
{
	char	**words;

	words = split_string(prompt, counter, n_head);
	if (!words)
		return (NULL);
	return (words);
}

token_t	*tokenize_input(const char *prompt, int *token_count,
		t_list_head *n_head)
{
	int		counter;
	char	**strs;
	token_t	*tokens;

	if (!prompt || !token_count)
		return (NULL);
	strs = splite_token(prompt, &counter, n_head);
	tokens = ft_malloc((counter + 1) * sizeof(token_t), n_head);
	if (!tokens)
		return (NULL);
	fill_tokens_array(tokens, strs, counter);
	*token_count = counter;
	return (tokens);
}
