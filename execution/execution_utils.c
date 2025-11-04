/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:14:16 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 16:19:07 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	emptystring_error(t_mini *ls)
{
	if (ls->commands[0][0] == '\0')
	{
		ft_str_error(ls, ": command not found\n", ls->commands[0]);
		ls->stat = 127;
		child_clean_up(ls);
		return (1);
	}
	return (0);
}

int	pipecount(t_mini *ls)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (ls->tokens[i])
	{
		if (!ft_strcmp(ls->tokens[i], "|"))
			x++;
		i++;
	}
	return (x);
}

int	countpointers(t_mini *ls, int *n)
{
	int	x;

	x = 0;
	while (ls->tokens[*n])
	{
		if (!ft_strcmp(ls->tokens[*n], "|"))
			break ;
		x++;
		(*n)++;
	}
	if (ls->tokens[*n])
		(*n)++;
	return (x);
}

char	**getcommand(t_mini *ls, int *f)
{
	int		i;
	int		j;
	int		x;
	char	**command;

	i = 0;
	j = *f;
	x = 0;
	x = countpointers(ls, f);
	command = malloc(sizeof(char *) * (x + 1));
	protect_malloc(ls, command);
	while (i < x)
	{
		command[i] = ft_strdup(ls->tokens[j]);
		clean_up(ls, i, (void ***)&command);
		i++;
		j++;
	}
	command[i] = NULL;
	return (command);
}

int	dopipe(t_mini *ls)
{
	int	i;

	i = -1;
	ls->pipefd = malloc(sizeof(int *) * ls->xpipe);
	protect_malloc(ls, ls->pipefd);
	while (++i < ls->xpipe)
	{
		ls->pipefd[i] = malloc(sizeof(int) * 2);
		clean_up(ls, i, (void ***)&ls->pipefd);
		if (pipe(ls->pipefd[i]) == -1)
		{
			while (--i > 0)
			{
				close(ls->pipefd[i][0]);
				close(ls->pipefd[i][1]);
			}
			ftfree(i, (void ***)&ls->pipefd);
			return (1);
		}
	}
	return (0);
}
