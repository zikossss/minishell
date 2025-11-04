/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:45:27 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/16 00:15:25 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_dir(t_mini *ls, int index, struct stat v)
{
	if (S_ISREG(v.st_mode))
	{
		ls->stat = 1;
		ft_str_error(ls, ": Not a directory\n", ls->commands[index]);
		return (1);
	}
	return (0);
}

int	check_error(t_mini *ls, int *index)
{
	struct stat	v;

	if (!stat(ls->commands[*index], &v))
	{
		if (check_dir(ls, *index, v))
			return (1);
	}
	else
	{
		perror("minishell");
		ls->stat = 1;
		return (1);
	}
	return (0);
}

int	parce_cd_arg(t_mini *ls, int index)
{
	if (check_to_many_args(ls) > 2)
	{
		ft_str_error(ls, ": too many arguments\n", ls->commands[0]);
		ls->stat = 1;
		return (1);
	}
	if (!ls->commands[index])
		return (1);
	if (check_error(ls, &index))
		return (1);
	return (0);
}

int	get_new_pwd(t_mini *ls)
{
	char	*strr;

	strr = getcwd(NULL, 0);
	if (cwd_error(ls, strr))
		return (1);
	if (ls->newpwd)
		free(ls->newpwd);
	ls->newpwd = ft_strdup(strr);
	free(strr);
	protect_malloc(ls, ls->newpwd);
	ch_env(&ls->exportenv, ls);
	ch_env(&ls->env, ls);
	ls->stat = 0;
	return (0);
}

void	cd(t_mini *ls, int *index)
{
	char	*cwd;

	(*index)++;
	if (parce_cd_arg(ls, *index))
		return ;
	if (ls->oldpwd)
		free(ls->oldpwd);
	ls->oldpwd = my_getenv(ls, "PWD");
	if (!ls->oldpwd)
	{
		cwd = getcwd(NULL, 0);
		if (cwd_error(ls, cwd))
			return ;
		ls->oldpwd = ft_strdup(cwd);
		free(cwd);
		protect_malloc(ls, ls->oldpwd);
	}
	if (chdir(ls->commands[*index]) == -1)
	{
		perror("minichell");
		ls->stat = 1;
		return ;
	}
	if (get_new_pwd(ls))
		return ;
}
