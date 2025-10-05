/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/05 18:35:47 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*extract_prefix(const char *str, int *dollar_pos, t_data *data)
{
	char	*prefix;
	int		j;
	int i;

	j = 0;
	while (str[j] && str[j] != '$')
		j++;
	*dollar_pos = j;
	if (!str[j])
		return (my_strdup(str, data->n_head));
	if(!str[j + 1])
		return (my_strdup(str, data->n_head));
	if(str[j + 1] == 32 || (str[j + 1] >= 9 && str[j + 1] <= 13))
	{
		i = j + 1;
		while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		{
			i++;
		}
		prefix = ft_malloc(((i - 1) * sizeof(char)), data->n_head);
		ft_strlcpy(prefix, str, i - 1);
		return (prefix);
	}
	prefix = ft_malloc(((j + 1) * sizeof(char)), data->n_head);
	ft_strlcpy(prefix, str, j + 1);
	return (prefix);
}

static int	get_var_name_length(const char *var_name)
{
	int	var_len;

	var_len = 0;
	if (var_name[0] == '?')
		return (1);
	while (var_name[var_len] && (ft_isalnum(var_name[var_len]) || var_name[var_len] == '_'))
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
		t_data *data)
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

char	*expand_variable(const char *str, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	int		dollar_pos;
	int		var_len;

	if (!str)
		return (my_strdup("", data->n_head));
	prefix = extract_prefix(str, &dollar_pos, data);
	if (!str[dollar_pos])
		return (prefix);
	var_name = (char *)(str + dollar_pos + 1);
	var_len = get_var_name_length(var_name);
	suffix = expand_variable(var_name + var_len, data);
	if (var_len == 1 && var_name[0] == '?')
		var_value = ft_itoa_with_head(data->exit_code, data->n_head);
	else
		var_value = find_env_value(var_name, var_len, data->env);
	if (var_value)
		return (build_result(prefix, var_value, suffix, data));
	return (build_result(prefix, "", suffix, data));
}
