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
	while (str[j] && str[j] != '$')
		j++;
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

static char	*extract_prefix(const char *str, int *dollar_pos, t_data *data)
{
	char	*prefix;
	int		j;

	j = find_dollar_position(str);
	*dollar_pos = j;
	if (!str[j] || !str[j + 1])
		return (my_strdup(str, data->n_head));
	if (str[j + 1] == 32 || (str[j + 1] >= 9 && str[j + 1] <= 13))
		return (handle_whitespace_after_dollar(str, j, data));
	prefix = ft_malloc(((j + 1) * sizeof(char)), data->n_head);
	ft_strlcpy(prefix, str, j + 1);
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
