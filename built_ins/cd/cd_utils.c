/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:45:42 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 23:23:42 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_to_many_args(t_mini *ls)
{
	int	i;

	i = 0;
	while (ls->commands[i])
		i++;
	return (i);
}

int	ft_dir_form(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			if (s[i + 1] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	cwd_error(t_mini *ls, char *cwd)
{
	if (!cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		ls->stat = 0;
		return (1);
	}
	return (0);
}
