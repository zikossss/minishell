/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:12:01 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 21:40:38 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addonetoclose(t_mini *ls, int x)
{
	if (x == 1)
		ls->outflag += 1;
	else if (x == 2)
		ls->inflag += 1;
	else if (x == 3)
		ls->outflag += 1;
}

int	thecorrectfd(t_mini *ls)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (ls->commands[i])
	{
		x = isredirection(ls, i);
		if (x && ls->commands[i + 1])
		{
			addonetoclose(ls, x);
			if (checkwhichtodo(x, ls, i))
				return (1);
			if ((x == 1 || x == 3) && ls->fd == -1)
				return (1);
			if (x == 2 && ls->infd == -1)
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

int	fork_built_ins(t_mini *ls, int *i)
{
	ls->pid = fork();
	if (ls->pid == -1)
	{
		perror("minishell: ");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	if (!ls->pid)
		execute_child(ls, *i);
	return (0);
}

int	aboutbuiltin(t_mini *ls, int *i)
{
	if (ls->xpipe)
	{
		if (fork_built_ins(ls, i))
			return (1);
	}
	else
	{
		ls->isbuiltin = 1;
		dupfor(ls);
		dobuiltin(ls, i);
	}
	return (1);
}

void	commandexec(t_mini *ls)
{
	int	i;

	i = -1;
	variablexpantion(ls, ls->commands);
	if (!ls->xpipe)
	{
		if (thecorrectfd(ls))
			return ;
		ls->commands = parce_line(ls);
	}
	while (ls->commands[++i])
	{
		if (isbuiltin(ls->commands[i]))
		{
			if (aboutbuiltin(ls, &i))
				break ;
		}
		else
		{
			if (ft_fork(ls, i))
				return ;
			break ;
		}
	}
}
