/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/22 18:19:34 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*extract_prefix(const char *str, int *dollar_pos,
		struct list_head *head)
{
	char	*prefix;
	int		j;

	j = 0;
	while (str[j] && str[j] != '$')
		j++;
	*dollar_pos = j;
	if (!str[j])
		return (my_strdup(str, head));
	prefix = ft_malloc(((j + 1) * sizeof(char)), head);
	ft_strlcpy(prefix, str, j + 1);
	return (prefix);
}

static int	get_var_name_length(const char *var_name)
{
	int	var_len;

	var_len = 0;
	while (var_name[var_len] && var_name[var_len] != ' '
		&& var_name[var_len] != '\t')
		var_len++;
	return (var_len);
}

static char	*find_env_value(const char *var_name, int var_len, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, var_len) == 0
			&& env->envp[i][var_len] == '=')
		{
			return (env->envp[i] + var_len + 1 );
		}
		i++;
	}
	return (NULL);
}

static char	*build_result(char *prefix, char *var_value, char *suffix,
		struct list_head *head)
{
	char	*result;
	int		total_len;

	total_len = ft_strlen(prefix) + ft_strlen(suffix) + ft_strlen(var_value);
	result = ft_malloc((total_len + 1) * sizeof(char), head);
	if (!result)
		return (NULL);
	ft_strcpy(result, prefix);
	ft_strlcat(result, var_value, total_len + 1);
	ft_strlcat(result, suffix, total_len + 1);
	return (result);
}

char	*expand_variable(const char *str, t_env *env, struct list_head *head) // "hello $PATH world"
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	int		dollar_pos;
	int		var_len;

	if (!str)
		return (my_strdup("", head));
	prefix = extract_prefix(str, &dollar_pos, head);
	if (!str[dollar_pos])
		return (prefix);
	var_name = (char *)(str + dollar_pos + 1);
	var_len = get_var_name_length(var_name);
	suffix = var_name + var_len;
	var_value = find_env_value(var_name, var_len, env);
	if (var_value)
		return (build_result(prefix, var_value, suffix, head));
	return (my_strdup("", head));
}
