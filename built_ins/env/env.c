/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:51:44 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 21:19:36 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_env(char **env)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	i = 0;
	j = 0;
	size = ft_strcount(env);
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ch_env(char ***env, t_mini *ls)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], PWD, 4) && !ls->is_pwd)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin(PWD, ls->newpwd);
			clean_up(ls, i, (void ***)env);
		}
		if (!ft_strncmp((*env)[i], OLDPWD, 7))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin(OLDPWD, ls->oldpwd);
			clean_up(ls, i, (void ***)env);
		}
		i++;
	}
	sort_env(*env);
}

char	**copy_env(t_mini *ls, char **env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * (ft_strcount(env) + 1));
	protect_malloc(ls, arr);
	while (env[i])
	{
		arr[i] = ft_strdup(env[i]);
		clean_up(ls, i, (void ***)&arr);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	vars_only(char **var, int i)
{
	int	j;

	j = 0;
	while (var[i])
	{
		if (!find_equal1(var[i]))
		{
			free(var[i]);
			j = i;
			while (var[j] && var[j + 1])
			{
				var[j] = var[j + 1];
				j++;
			}
			var[j] = NULL;
		}
		else
			i++;
	}
}

void	env(t_mini *ls)
{
	int	i;

	i = 0;
	if (ls->env)
		ft_free(&ls->env);
	ls->env = copy_env(ls, ls->exportenv);
	if (ls->commands[i + 1])
	{
		ft_str_error(ls, ": No such file or directory\n", ls->commands[i + 1]);
		ls->stat = 127;
		return ;
	}
	vars_only(ls->env, i);
	print_env(ls);
	ls->stat = 0;
}
