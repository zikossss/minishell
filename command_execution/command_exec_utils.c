/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:12:58 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 03:13:40 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(t_mini *ls, char *var)
{
	char	*env;
	int		i;

	i = 0;
	while (ls->env[i])
	{
		if (!ft_strncmp(ls->env[i], var, ft_strlen(var)))
		{
			env = takevalue(ls, ls->env[i], ft_strlen(var) + 1);
			return (env);
		}
		i++;
	}
	return (NULL);
}

int	error_check(t_mini *ls, int i, int x)
{
	if (!ls->cn_flag && x)
	{
		ft_str_error(ls, ": Permission denied\n", ls->path[x]);
		ls->stat = 126;
		return (-1);
	}
	if (!ls->cn_flag && (!ft_strcmp(ls->commands[i], "$")
			|| ft_strncmp(ls->commands[i], "$", 1)))
	{
		ft_str_error(ls, ": command not found\n", ls->commands[i]);
		ls->stat = 127;
		return (-1);
	}
	return (0);
}

int	check_pd_cf(t_mini *ls, int i)
{
	int	x;
	int	j;

	x = 0;
	j = 0;
	while (ls->path[j])
	{
		if (!access(ls->path[j], F_OK))
		{
			x = j;
			if (!access(ls->path[j], X_OK))
				return (j);
		}
		j++;
	}
	if (error_check(ls, i, x) == -1)
		return (-1);
	return (0);
}

int	isaccesiblecommand(t_mini *ls, int i)
{
	int		j;
	char	*path;

	j = 0;
	if (!ft_strchar(ls->commands[i], '/'))
	{
		path = my_getenv(ls, "PATH");
		if (!path)
			return (-2);
		ls->path = ft_splitpath(path, ':', ls->commands[i]);
		free(path);
		protect_malloc(ls, ls->path);
		j = check_pd_cf(ls, i);
		if (j >= -1)
			return (j);
	}
	return (-2);
}
