/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:56:08 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:10:19 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_mini *ls)
{
	ft_free(&ls->env);
	ls->env = copy_env(ls, ls->exportenv);
	ls->stat = 0;
}

void	unset_env(t_mini *ls, int index)
{
	int	j;

	j = -1;
	while (ls->exportenv[++j])
	{
		if (!ft_strncmp(ls->commands[index], ls->exportenv[j],
				ft_strlen(ls->commands[(index)])))
		{
			free(ls->exportenv[j]);
			while (ls->exportenv[j] && ls->exportenv[j + 1])
			{
				if (ls->exportenv[j] && ls->exportenv[j + 1])
					ls->exportenv[j] = ls->exportenv[j + 1];
				j++;
			}
			ls->exportenv[j] = NULL;
			break ;
		}
	}
}

void	unset(t_mini *ls, int *index)
{
	while (ls->commands[++(*index)])
	{
		if (!ft_strcmp(ls->commands[(*index)], "PWD"))
			ls->is_pwd = 1;
		unset_env(ls, *index);
	}
	update_env(ls);
}
