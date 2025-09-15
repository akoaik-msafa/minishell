/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:40:00 by msafa             #+#    #+#             */
/*   Updated: 2025/09/15 02:06:11 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	compare_strings(const void *a, const void *b)
{
	return (strcmp(*(char **)a, *(char **)b));
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
int ft_strlen(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return(i);
}
int validate_variable(char *arg, char **output)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (!(arg[0] == '_' || (arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!(arg[i] == '_' || (arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z') || (arg[i] >= '0' && arg[i] <= '9')))
			return (0);
		i++;
	}
	if (arg[i] == '=')
		flag = 1;
	if (!flag)
		*output = arg;
	else
		*output = NULL;
	return (1);
}
int	ft_export(char *arg, char ***env)
{	
	int count;
	int i;
	int j;
	int k;
	char *temp;
	char *output;
	char **new_env;
	
	count = ft_strlen(*env);
	i = 0;
	j = 0;
	k = 0;
	if(!arg)
	{
		char **sorted_env = malloc(sizeof(char *) * (count + 1));
		if (!sorted_env)
			return (1);
		for (i = 0; i < count; i++)
			sorted_env[i] = (*env)[i];
		sorted_env[count] = NULL;

		i = 0;
		while(i < count)
		{
			k = 0;
			while(k < count - i - 1)
			{
				if(ft_strcmp(sorted_env[k], sorted_env[k + 1]) > 0)
				{
					temp = sorted_env[k];
					sorted_env[k] = sorted_env[k + 1];
					sorted_env[k + 1] = temp;
				}
				k++;
			}
			i++;
		}
		j = 0;
		while(sorted_env[j])
		{
			printf("%s\n", sorted_env[j]);
			j++;
		}
		free(sorted_env);
	}
	else
	{
		if(validate_variable(arg, &output))
		{
			int f = 0;
			while (*env && (*env)[f])
				f++;
			new_env = malloc(sizeof(char *) * (f + 2));
			if (!new_env)
				return (1);
			for (j = 0; j < f; j++)
				new_env[j] = (*env)[j];
			if (!output)
				new_env[f] = strdup(arg);
			else
				new_env[f] = strdup(output);
			new_env[f + 1] = NULL;
			if (*env != NULL)
				free(*env);
			*env = new_env;
		}
		else
		{
			printf("export: not a valid identifier: %s\n", arg);
			return (1);
		}
	}
	return(0);
}

int	ft_unset(char *arg, char **env)
{
	(void)env;
	if (arg)
		printf("unset command: %s\n", arg);
	else
		printf("unset command: no args\n");
	return (0);
}

int	ft_env(char *arg, char **env)
{
	int	i;

	(void)arg;
	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char *arg, char **env)
{
	(void)env;
	if (arg)
		printf("exit command: %s\n", arg);
	else
		printf("exit command: no args\n");
	return (0);
}
