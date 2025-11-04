/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:15:08 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 22:49:07 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initff(t_mini *ls)
{
	ft_free(&ls->path);
	ls->cn_flag = 0;
	ls->inflag = 0;
	ls->outflag = 0;
	ls->isbuiltin = 0;
	ls->outfile = 0;
	ls->infile = 0;
	if (ls->fd > 2)
		close(ls->fd);
	if (ls->infd > 2)
		close(ls->infd);
	ls->fd = 1;
	ls->infd = 0;
	ls->isambiguous = 0;
	ls->heredocfd = 0;
}

int	ft_fork(t_mini *ls, int i)
{
	ls->pid = fork();
	if (ls->pid == -1)
	{
		perror("minishell");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	if (!ls->pid)
		execute_child(ls, i);
	ft_free(&ls->commands);
	ft_free(&ls->path);
	return (0);
}

void	ft_freepipe(t_mini *ls)
{
	int	i;

	i = 0;
	while (i < ls->xpipe)
	{
		free(ls->pipefd[i]);
		i++;
	}
	free(ls->pipefd);
	ls->pipefd = NULL;
}

void	update_exitstat(t_mini *ls)
{
	int	stat;

	stat = 0;
	if (ls->pid)
	{
		waitpid(ls->pid, &ls->stat, 0);
		if (WIFEXITED(ls->stat))
			ls->stat = WEXITSTATUS(ls->stat);
		else if (WIFSIGNALED(ls->stat))
		{
			stat = 128 + WTERMSIG(ls->stat);
			if (stat == 130)
			{
				write(1, "\n", 1);
				ls->stat = 130;
			}
			else if (stat == 131)
			{
				write(2, "\n", 1);
				ls->stat = 131;
			}
		}
		while (wait(NULL) > 0)
			;
	}
}

void	execution(t_mini *ls)
{
	int	f;

	f = 0;
	ls->xpipe = pipecount(ls);
	if (ls->xpipe > 0)
		if (dopipe(ls))
			return ;
	initff(ls);
	if (ls->xpipe == 0)
		ls->v = count_herdoc(ls->tokens) - 1;
	while (ls->compos <= ls->xpipe)
	{
		ls->commands = getcommand(ls, &f);
		commandexec(ls);
		closepipefds(ls);
		initff(ls);
		ft_free(&ls->commands);
		ls->v++;
		ls->compos++;
	}
	update_exitstat(ls);
	signal(SIGINT, SIG_DFL);
	ft_free(&ls->files);
	ft_freepipe(ls);
}
