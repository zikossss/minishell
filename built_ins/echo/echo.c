/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:50:26 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 01:50:42 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_new_line(char **line, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (line[*i])
	{
		if (!ft_strncmp(line[*i], "-n", 2))
		{
			j = 1;
			while (line[*i][j])
			{
				if (line[*i][j] != 'n')
					return (x);
				j++;
			}
			x = 1;
		}
		else
			break ;
		(*i)++;
	}
	return (x);
}

void	print_fd(t_mini *ls)
{
	int	d;
	int	i;

	i = 1;
	d = is_new_line(ls->commands, &i);
	while (ls->commands[i])
	{
		ft_putstr_fd1(ls->commands[i], ls->fd);
		if (ls->commands[i + 1])
			ft_putstr_fd(" ", ls->fd);
		i++;
	}
	if (!d)
		ft_putstr_fd("\n", ls->fd);
}

int	count_non_redirections(t_mini *ls)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ls->commands[i])
	{
		if (isredirection(ls, i) && ls->commands[i + 1])
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}

char	**parce_line(t_mini *ls)
{
	char	**commands;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = count_non_redirections(ls);
	commands = malloc(sizeof(char *) * (count + 1));
	protect_malloc(ls, commands);
	while (ls->commands[i])
	{
		if (isredirection(ls, i) && ls->commands[i + 1])
		{
			i += 2;
			continue ;
		}
		commands[j] = ft_strdup(ls->commands[i]);
		clean_up(ls, j, (void ***)&commands);
		i++;
		j++;
	}
	commands[j] = NULL;
	ft_free(&ls->commands);
	return (commands);
}

void	echo(t_mini *ls, int *i)
{
	(*i)++;
	if (!ls->commands[*i])
	{
		ft_putstr_fd("\n", ls->fd);
		return ;
	}
	if (ls->fd >= 1)
	{
		print_fd(ls);
	}
	ls->stat = 0;
}
