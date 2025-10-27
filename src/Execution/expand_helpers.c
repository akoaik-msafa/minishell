/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:00:00 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/27 22:51:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_var_name_length(const char *var_name)
{
	int	var_len;

	var_len = 0;
	if (var_name[0] == '?')
		return (1);
	while (var_name[var_len] && (ft_isalnum(var_name[var_len])
			|| var_name[var_len] == '_'))
		var_len++;
	return (var_len);
}

char	*find_env_value(const char *var_name, int var_len, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, var_len) == 0
			&& env->envp[i][var_len] == '=')
		{
			return (env->envp[i] + var_len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*build_result(char *prefix, char *var_value, char *suffix, t_data *data)
{
	char	*result;
	int		total_len;

	total_len = ft_strlen(prefix) + ft_strlen(suffix) + ft_strlen(var_value);
	result = ft_malloc((total_len + 1) * sizeof(char), data->n_head);
	if (!result)
		return (NULL);
	ft_strcpy(result, prefix);
	ft_strlcat(result, var_value, total_len + 1);
	ft_strlcat(result, suffix, total_len + 1);
	return (result);
}

int	find_dollar_position(const char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\\' && str[j + 1] == '$')
			j += 2;
		else if (str[j] == '$')
			break ;
		else
			j++;
	}
	return (j);
}

char	*handle_whitespace_after_dollar(const char *str, int j,
		t_data *data)
{
	char	*prefix;
	int		i;

	i = j + 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	prefix = ft_malloc(((i - 1) * sizeof(char)), data->n_head);
	ft_strlcpy(prefix, str, i - 1);
	return (prefix);
}
