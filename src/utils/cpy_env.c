/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:38:12 by akoaik            #+#    #+#             */
/*   Updated: 2025/09/30 02:37:52 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static char	*copy_env(char *src, t_list_head *head)
{
	char	*dest;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = ft_malloc(len + 1, head);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int init_env(t_env *env, char **envp, t_list_head *head)
{
    int i;

    if (!env || !envp)
        return (0);

    env->count = count_env(envp);
    env->envp = ft_malloc((env->count + 1) * sizeof(char *), head);
    if (!env->envp)
        return (0);

    i = 0;
    while (i < env->count)
    {
        env->envp[i] = copy_env(envp[i], head);
        if (!env->envp[i])
            return (0);
        i++;
    }
    env->envp[i] = NULL;

    env->export_only = ft_malloc(sizeof(char *) * (env->count + 1), head);
    if (!env->export_only)
        return (0);

    i = 0;
    while (i < env->count)
    {
        env->export_only[i] = my_strdup(env->envp[i], head);
        i++;
    }
    env->export_only[env->count] = NULL;

    int env_index = find_env_var("SHLVL", env->envp);
    int export_index = find_env_var("SHLVL", env->export_only);

    if (env_index == -1)
    {
        add_to_env("SHLVL=0", env, head);
        add_to_export_only("SHLVL=1", env, head);
    }
    else
    {
        int current_shlvl = ft_atoi(env->envp[env_index] + 6);
        char *new_shlvl_str = ft_itoa_with_head(current_shlvl + 1, head);

        if (export_index != -1)
        {
            char *new_export_entry = ft_malloc(ft_strlen("SHLVL=") + ft_strlen(new_shlvl_str) + 1, head);
            if (new_export_entry)
            {
                ft_strcpy(new_export_entry, "SHLVL=");
                ft_strcat(new_export_entry, new_shlvl_str);
                env->export_only[export_index] = new_export_entry;
            }
        }
        else
        {
            char *new_export_entry = ft_malloc(ft_strlen("SHLVL=") + ft_strlen(new_shlvl_str) + 1, head);
            if (new_export_entry)
            {
                ft_strcpy(new_export_entry, "SHLVL=");
                ft_strcat(new_export_entry, new_shlvl_str);
                add_to_export_only(new_export_entry, env, head);
            }
        }
    }

    return (1);
}

char	**get_env(t_env *env)
{
	if (!env->envp)
		return (NULL);
	return (env->envp);
}

int	get_env_count(t_env *env)
{
	if (!env)
		return (0);
	return (env->count);
}

char	*ft_itoa_with_head(int n, t_list_head *head)
{
	char	*temp;
	char	*result;

	temp = ft_itoa(n);
	if (!temp)
		return (NULL);
	result = copy_env(temp, head);
	free(temp);
	return (result);
}

void	add_to_export_only(char *arg, t_env *env, t_list_head *env_head)
{
	int		count;
	int		i;
	char	**new_export;

	count = 0;
	while (env->export_only && env->export_only[count])
		count++;
	new_export = ft_malloc(sizeof(char *) * (count + 2), env_head);
	if (!new_export)
		return ;
	i = 0;
	while (i < count)
	{
		new_export[i] = env->export_only[i];
		i++;
	}
	new_export[count] = copy_env(arg, env_head);
	new_export[count + 1] = NULL;
	env->export_only = new_export;
}
