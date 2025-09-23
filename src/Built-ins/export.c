/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:53:42 by msafa             #+#    #+#             */
/*   Updated: 2025/09/23 15:47:36 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char *ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	while(dest[i])
		i++;
	j = 0;
	while(src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return(dest);
}


char *ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*dup;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int array_len(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return(i);
}

int validate_identifier(char *arg)
{
	int i;

	i = 0;
	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_'))
		return (0);
	while(arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z') || arg[i] == '_' || (arg[i] >= '0' && arg[i] <= '9')))
			return(0);
		i++;
	}
	return (1);
}

int find_env_var(char *var_name, char **env)
{
	int i;
	int len;

	if (!var_name || !env)
		return (-1);
	len = 0;
	while (var_name[len] && var_name[len] != '=' && var_name[len] != '+')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void append_to_env(char *arg, t_env *env, int index, t_list_head *env_head)
{
	char *new_value;
	char *result;
	int existing_len;
	int new_len;

	new_value = ft_strchr(arg, '=');
	if (!new_value)
		return;
	new_value++;
	existing_len = ft_strlen(env->envp[index]);
	new_len = ft_strlen(new_value);
	result = ft_malloc((existing_len + new_len + 1),env_head);
	if (!result)
		return;
	ft_strcpy(result, env->envp[index]);
	ft_strcat(result, new_value);
	env->envp[index] = result;
}

void update_env(char *arg, t_env *env, int index, t_list_head *env_head)
{
	env->envp[index] = my_strdup(arg,env_head);
}

void add_to_env(char *arg, t_env *env, t_list_head *env_head)
{
	int count;
	int i;
	char **new_env;

	count = array_len(env->envp);
	new_env = ft_malloc(sizeof(char *) * (count + 2),env_head);
	if (!new_env)
		return;
	i = 0;
	while (i < count)
	{
		new_env[i] = (env->envp)[i];
		i++;
	}
	new_env[count] = my_strdup(arg,env_head);
	new_env[count + 1] = NULL;
	env->envp = new_env;
}

void add_var_no_value(char *arg, t_env *env, t_list_head *env_head)
{
	int count;
	int i;
	char **new_export;

	if (!env->export_only)
	{
		env->export_only = ft_malloc(sizeof(char *) * 2,env_head);
		if (!env->export_only)
			return;
		(env->export_only)[0] = my_strdup(arg,env_head);
		(env->export_only)[1] = NULL;
		return;
	}
	count = array_len(env->export_only);
	new_export = ft_malloc(sizeof(char *) * (count + 2),env_head);
	if (!new_export)
		return;
	i = 0;
	while (i < count)
	{
		new_export[i] = (env->export_only)[i];
		i++;
	}
	new_export[count] = my_strdup(arg,env_head);
	new_export[count + 1] = NULL;
	env->export_only = new_export;
}

int	ft_export(char *arg, t_env *env,t_list_head *n_head,t_list_head *env_head)
{
	int count;
	int i;
	int j;
	char *temp;
	char **sorted_env;
    int export_count;
    int index;
	char *equal_pos;

	if (!arg)
	{
        env->count = array_len(env->envp);
		if (env->export_only)
			export_count = array_len(env->export_only);
		else
			export_count = 0;
		count = env->count + export_count;
		sorted_env = ft_malloc(sizeof(char *) * (count + 1),n_head);
		if (!sorted_env)
			return (1);
		i = 0;
		while (i < env->count)
		{
			sorted_env[i] = (env->envp)[i];
			i++;
		}
		j = 0;
		while (j < export_count)
		{
			sorted_env[i + j] = (env->export_only)[j];
			j++;
		}
		sorted_env[count] = NULL;
		i = 0;
		while (i < count)
		{
			j = 0;
			while (j < count - i - 1)
			{
				if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
				{
					temp = sorted_env[j];
					sorted_env[j] = sorted_env[j + 1];
					sorted_env[j + 1] = temp;
				}
				j++;
			}
			i++;
		}
		i = 0;
		while (sorted_env[i])
		{
			equal_pos = ft_strchr(sorted_env[i],'=');
			if(equal_pos)
			{
				*equal_pos = '\0';
				printf("declare -x %s=\"%s\"\n",sorted_env[i],equal_pos + 1);
				*equal_pos = '=';
			}
			else
				printf("declare -x %s\n", sorted_env[i]);
			i++;
		}
	}
	else
	{	
		if(validate_identifier(arg))
		{
			i = 0;
			while(arg[i] && arg[i] != '=')
				i++;
			index = find_env_var(arg, env->envp);
			if (index != -1)
			{
				if (arg[i] == '=' && i > 0 && arg[i - 1] == '+')
				{
					append_to_env(arg, env, index,env_head);
				}
				else if (arg[i] == '=')
				{
					update_env(arg, env, index,env_head);
				}
			}
			else
			{
				if (arg[i] == '=')
				{
					add_to_env(arg, env,env_head);
				}
				else
				{
					add_var_no_value(arg, env,env_head);
				}
			}
		}
		else
		{
			write(2,"minishell: export: ",20);
			printf("`%s': not a valid identifier\n",arg);
			return(0);
		}
	}
	return (0);
}
