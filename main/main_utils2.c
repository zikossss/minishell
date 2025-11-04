/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:41:58 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 22:53:50 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_up(t_mini *ls, int i, void ***arr)
{
	if (!(*arr)[i])
	{
		ftfree(i, arr);
		my_exit(ls);
	}
}

void	init_intigires(t_mini *ls)
{
	ls->fd = 1;
	ls->v = 0;
	ls->okay = 0;
	ls->xpipe = 0;
	ls->infile = 0;
	ls->outfile = 0;
	ls->heredoc = 0;
	ls->cn_flag = 0;
	ls->pid = 0;
	ls->infd = 0;
	ls->is_pwd = 0;
	ls->compos = 0;
	ls->isbuiltin = 0;
	ls->stat = 0;
	ls->inflag = 0;
	ls->outflag = 0;
	ls->expand = 0;
	ls->heredocfd = 0;
	ls->start = 0;
	ls->isambiguous = 0;
}

void	init_struct(t_mini *ls)
{
	ls->exportenv = NULL;
	ls->env = NULL;
	ls->pipecommand = NULL;
	ls->oldpwd = NULL;
	ls->newpwd = NULL;
	ls->commands = NULL;
	ls->path = NULL;
	ls->linefromread = NULL;
	ls->heredocdelimiter = NULL;
	ls->tokens = NULL;
	ls->files = NULL;
	ls->file = NULL;
	ls->pipefd = NULL;
	init_intigires(ls);
}

void	execute_child(t_mini *ls, int i)
{
	int	stat;

	stat = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ls->xpipe > 0)
	{
		if (thecorrectfd(ls))
			exit(ls->stat);
		ls->commands = parce_line(ls);
	}
	isfrompath(ls, i);
	stat = ls->stat;
	free(ls);
	exit(stat);
}
