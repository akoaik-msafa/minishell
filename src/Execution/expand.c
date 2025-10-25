/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:42:30 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/12 19:35:54 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	find_dollar_position(const char *str)
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

static char	*handle_whitespace_after_dollar(const char *str, int j,
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

static char	*remove_backslash_escapes(const char *str, t_data *data)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	result = ft_malloc((len + 1) * sizeof(char), data->n_head);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			result[j++] = '$';
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static char	*extract_prefix(const char *str, int *dollar_pos, t_data *data)
{
	char	*prefix;
	char	*temp;
	int		j;
	int		i;
	int		k;

	j = find_dollar_position(str);
	*dollar_pos = j;
	if (!str[j] || !str[j + 1])
		return (remove_backslash_escapes(str, data));
	if (str[j + 1] == 32 || (str[j + 1] >= 9 && str[j + 1] <= 13))
		return (handle_whitespace_after_dollar(str, j, data));
	temp = ft_malloc(((j + 1) * sizeof(char)), data->n_head);
	ft_strlcpy(temp, str, j + 1);
	prefix = ft_malloc(((j + 1) * sizeof(char)), data->n_head);
	i = 0;
	k = 0;
	while (temp[i])
	{
		if (temp[i] == '\\' && temp[i + 1] == '$')
		{
			prefix[k++] = '$';
			i += 2;
		}
		else
			prefix[k++] = temp[i++];
	}
	prefix[k] = '\0';
	return (prefix);
}

char	*expand_variable(const char *str, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	int		var_len;

	if (!str)
		return (my_strdup("", data->n_head));
	prefix = extract_prefix(str, &var_len, data);
	if (!str[var_len])
		return (prefix);
	var_name = (char *)(str + var_len + 1);
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

int	has_unescaped_dollar(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			i += 2;
		else if (str[i] == '$')
			return (1);
		else
			i++;
	}
	return (0);
}

char	*remove_escape_dollar(const char *str, t_data *data)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (my_strdup("", data->n_head));
	len = ft_strlen(str);
	result = ft_malloc((len + 1) * sizeof(char), data->n_head);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			result[j++] = '$';
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
