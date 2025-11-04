/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:47:49 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:48:10 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dostdout(char *filename, t_mini *ls)
{
	if (ls->outflag > 1 && ls->fd > 2)
		close(ls->fd);
	if (opendir(filename))
	{
		ls->stat = 1;
		ls->fd = -1;
		ft_str_error(ls, ": Is a directory\n", filename);
		return (1);
	}
	if (ls->isambiguous)
	{
		ls->stat = 1;
		ls->fd = -1;
		ft_str_error(ls, ": ambiguous redirect\n", filename);
		return (1);
	}
	ls->fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ls->fd == -1)
	{
		ls->stat = 1;
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	doappend(char *filename, t_mini *ls)
{
	if (ls->outflag > 1 && ls->fd > 2)
		close(ls->fd);
	if (opendir(filename))
	{
		ls->stat = 1;
		ls->fd = -1;
		ft_str_error(ls, ": Is a directory\n", filename);
		return (1);
	}
	if (ls->isambiguous)
	{
		ls->stat = 1;
		ls->fd = -1;
		ft_str_error(ls, ": ambiguous redirect\n", filename);
		return (1);
	}
	ls->fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (ls->fd == -1)
	{
		ls->stat = 1;
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	dostdin(char *filename, t_mini *ls)
{
	if (ls->inflag > 1 && ls->infd > 2)
		close(ls->infd);
	if (opendir(filename))
	{
		ls->stat = 1;
		ls->infd = -1;
		ft_str_error(ls, ": Is a directory\n", filename);
		return (1);
	}
	if (ls->isambiguous)
	{
		ls->stat = 1;
		ls->infd = -1;
		ft_str_error(ls, ": ambiguous redirect\n", filename);
		return (1);
	}
	ls->infd = open(filename, O_RDONLY, 0644);
	if (ls->infd == -1)
	{
		ls->stat = 1;
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	checkwhichtodo(int x, t_mini *ls, int i)
{
	int	d;

	d = 0;
	if (x == 1)
		d = dostdout(ls->commands[i + 1], ls);
	else if (x == 2)
		d = dostdin(ls->commands[i + 1], ls);
	else if (x == 3)
		d = doappend(ls->commands[i + 1], ls);
	return (d);
}

int	isredirection(t_mini *ls, int i)
{
	if (!ft_strcmp(ls->commands[i], ">"))
	{
		ls->outfile = 1;
		return (1);
	}
	else if (!ft_strcmp(ls->commands[i], "<"))
	{
		ls->infile = 1;
		return (2);
	}
	else if (!ft_strcmp(ls->commands[i], ">>"))
	{
		ls->outfile = 1;
		return (3);
	}
	else if (!ft_strcmp(ls->commands[i], "<<"))
		return (4);
	return (0);
}
