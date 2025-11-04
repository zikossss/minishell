/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:13:34 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 21:41:41 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dupfor_pipe(t_mini *ls)
{
	if (ls->compos > 0 && !ls->isbuiltin && !ls->infile && ls->heredocfd <= 0)
	{
		dup2(ls->pipefd[ls->compos - 1][0], STDIN_FILENO);
		close(ls->pipefd[ls->compos - 1][1]);
	}
	if (ls->isbuiltin && ls->compos < ls->xpipe && !ls->outfile)
	{
		ls->fd = ls->pipefd[ls->compos][1];
		close(ls->pipefd[ls->compos][0]);
	}
	else if (ls->compos < ls->xpipe && !ls->outfile)
	{
		dup2(ls->pipefd[ls->compos][1], STDOUT_FILENO);
		close(ls->pipefd[ls->compos][0]);
	}
}

void	dupfor(t_mini *ls)
{
	if (ls->outfile && !ls->isbuiltin)
	{
		dup2(ls->fd, STDOUT_FILENO);
		close(ls->fd);
	}
	if (ls->infile && !ls->isbuiltin)
	{
		dup2(ls->infd, STDIN_FILENO);
		close(ls->infd);
	}
	if (!ls->infile && ls->files && !ls->okay && !ls->isbuiltin)
	{
		ls->heredocfd = open(ls->files[ls->v], O_RDWR);
		if (ls->heredocfd != -1)
		{
			dup2(ls->heredocfd, STDIN_FILENO);
			close(ls->heredocfd);
		}
	}
	if (ls->xpipe > 0)
		dupfor_pipe(ls);
}

void	closepipefds(t_mini *ls)
{
	if (ls->xpipe)
	{
		if (ls->compos == 0)
			close(ls->pipefd[ls->compos][1]);
		if (ls->compos > 0)
		{
			if (ls->compos < ls->xpipe)
			{
				close(ls->pipefd[ls->compos - 1][0]);
				close(ls->pipefd[ls->compos][1]);
			}
			else if (ls->compos == ls->xpipe && !ls->isbuiltin)
				close(ls->pipefd[ls->compos - 1][0]);
		}
	}
}

void	protect_malloc(t_mini *ls, void *str)
{
	if (!str)
		my_exit(ls);
}

void	builtin_execute_child(t_mini *ls, int *i)
{
	int	stat;

	stat = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ls->isbuiltin = 1;
	if (ls->xpipe > 0)
	{
		if (thecorrectfd(ls))
			exit(ls->stat);
		ls->commands = parce_line(ls);
	}
	dupfor(ls);
	dobuiltin(ls, i);
	stat = ls->stat;
	free(ls);
	exit(stat);
}
