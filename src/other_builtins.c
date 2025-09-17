/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/18 02:13:50 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	compare_strings(const void *a, const void *b)
{
	return (ft_strcmp(*(char **)a, *(char **)b));
}

int	ft_pwd(char *arg)
{
	char	*cwd;

	(void)arg;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
int array_len(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return(i);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

char *ft_strcat(char *dest, char *src)
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

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(dest);
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	while(i < n && s1[i] && s2[i])
	{
		if(s1[i] != s2[i])
			return(s1[i] - s2[i]);
		i++;
	}
	if(i < n)
		return(s1[i] - s2[i]);
	return(0);
}

int	ft_export(char *arg, t_env_data *env_data)
{
	int count;
	int i;
	int j;
	char *temp;
	char **sorted_env;

	if (!arg)
	{
		int env_count = array_len(env_data->env);
		int export_count;
		if (env_data->export_only)
			export_count = array_len(env_data->export_only);
		else
			export_count = 0;
		count = env_count + export_count;
		sorted_env = malloc(sizeof(char *) * (count + 1));
		if (!sorted_env)
			return (1);
		i = 0;
		while (i < env_count)
		{
			sorted_env[i] = (env_data->env)[i];
			i++;
		}
		j = 0;
		while (j < export_count)
		{
			sorted_env[i + j] = (env_data->export_only)[j];
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
			printf("declare -x %s\n", sorted_env[i]);
			i++;
		}
		free(sorted_env);
	}
	else
	{
		if(validate_identifier(arg))
		{
			i = 0;
			while(arg[i] && arg[i] != '=')
				i++;
			int index = find_env_var(arg, env_data->env);
			if (index != -1)
			{
				if (arg[i] == '=' && i > 0 && arg[i - 1] == '+')
				{
					append_to_env(arg, env_data, index);
				}
				else if (arg[i] == '=')
				{
					update_env(arg, env_data, index);
				}
			}
			else
			{

				if (arg[i] == '=')
				{
					add_to_env(arg, env_data);
				}
				else
				{
					add_var_no_value(arg, env_data);
				}
			}
		}
		else
		{
			write(2,"minishell: export: ",20);
			printf("`%s': not a valid identifier",arg);
			exit(1);
		}
	}
	return (0);
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

void append_to_env(char *arg, t_env_data *env_data, int index)
{
	char *new_value;
	char *result;
	int existing_len;
	int new_len;

	new_value = strchr(arg, '=');
	if (!new_value)
		return;
	new_value++;

	existing_len = ft_strlen(env_data->env[index]);
	new_len = ft_strlen(new_value);

	result = malloc(existing_len + new_len + 1);
	if (!result)
		return;

	ft_strcpy(result, env_data->env[index]);
	ft_strcat(result, new_value);

	free(env_data->env[index]);
	env_data->env[index] = result;
}

void update_env(char *arg, t_env_data *env_data, int index)
{
	free(env_data->env[index]);
	env_data->env[index] = ft_strdup(arg);
}

void add_to_env(char *arg, t_env_data *env_data)
{
	int count;
	int i;
	char **new_env;

	count = array_len(env_data->env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return;

	i = 0;
	while (i < count)
	{
		new_env[i] = (env_data->env)[i];
		i++;
	}
	new_env[count] = ft_strdup(arg);
	new_env[count + 1] = NULL;

	free(env_data->env);
	env_data->env = new_env;
}

void add_var_no_value(char *arg, t_env_data *env_data)
{
	int count;
	int i;
	char **new_export;

	if (!env_data->export_only)
	{
		env_data->export_only = malloc(sizeof(char *) * 2);
		if (!env_data->export_only)
			return;
		(env_data->export_only)[0] = ft_strdup(arg);
		(env_data->export_only)[1] = NULL;
		return;
	}

	count = array_len(env_data->export_only);
	new_export = malloc(sizeof(char *) * (count + 2));
	if (!new_export)
		return;

	i = 0;
	while (i < count)
	{
		new_export[i] = (env_data->export_only)[i];
		i++;
	}
	new_export[count] = ft_strdup(arg);
	new_export[count + 1] = NULL;

	free(env_data->export_only);
	env_data->export_only = new_export;
}

int	ft_unset(char *arg, t_env_data *env_data)
{
	int index;

	if(!arg || !env_data)
		return(1);
	index = find_env_var(arg,env_data->env);
	if(index != -1)
	{
		free(env_data->env[index]);
		while(env_data->env[index + 1])
		{
			env_data->env[index] = env_data->env[index + 1];
			index++;
		}
		env_data->env[index] = NULL;
	}
	if(env_data->export_only)
	{
		index = find_env_var(arg,env_data->export_only);
		if(index != -1)
		{
			free(env_data->export_only[index]);
			while(env_data->export_only[index + 1])
			{
				env_data->export_only[index] = env_data->export_only[index + 1];
				index++;
			}
			env_data->export_only[index] = NULL;
		}
	}
	return(0);
}

int	ft_env(char *arg, t_env_data *env_data)
{
	int	i;

	(void)arg;
	if (!env_data || !env_data->env)
		return (1);
	i = 0;
	while (env_data->env[i])
	{
		printf("%s\n", env_data->env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char *arg, t_env_data *env_data)
{
	(void)env_data;
	if (arg)
		printf("exit command: %s\n", arg);
	else
		printf("exit command: no args\n");
	return (0);
}
