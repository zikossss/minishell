/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:41:43 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 23:27:57 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_clean_up(t_mini *ls)
{
	ft_free(&ls->commands);
	free(ls->linefromread);
	ls->linefromread = NULL;
	ft_free(&ls->env);
	ft_free(&ls->exportenv);
	ft_free(&ls->tokens);
	ft_free(&ls->path);
}

int	check_stat(t_mini *ls, int i)
{
	struct stat	v;

	if (!stat(ls->commands[i], &v))
	{
		if (S_ISREG(v.st_mode))
		{
			if (ls->commands[i][0] == '.' && !access(ls->commands[i], X_OK))
				return (1);
			else if (ls->commands[i][0] == '.' && access(ls->commands[i],
						X_OK) == -1)
				ft_str_error(ls, ": Permission denied\n", ls->commands[i]);
			else
				ft_str_error(ls, ": Not a directory\n", ls->commands[i]);
			ls->stat = 126;
			child_clean_up(ls);
			return (1);
		}
		if (S_ISDIR(v.st_mode))
		{
			ft_str_error(ls, ": Is a directory\n", ls->commands[i]);
			ls->stat = 126;
			return (1);
		}
	}
	return (0);
}

int	execute_command(t_mini *ls, int i)
{
	if (execve(ls->commands[i], ls->commands, ls->env))
	{
		if (check_stat(ls, i))
			return (1);
		perror("minishell");
		if (errno == ENOENT)
		{
			ls->stat = 127;
			child_clean_up(ls);
			return (1);
		}
	}
	return (0);
}

void	isfrompath(t_mini *ls, int i)
{
	int	j;

	j = isaccesiblecommand(ls, i);
	if (j == -1)
	{
		child_clean_up(ls);
		return ;
	}
	dupfor(ls);
	if (j == -2)
		if (execute_command(ls, i))
			return ;
	if (execve(ls->path[j], ls->commands, ls->env))
	{
		if (emptystring_error(ls))
			return ;
		perror("minishell");
		ls->stat = 126;
		child_clean_up(ls);
	}
}

void	begin_work(t_mini *ls)
{
	if (isclose(ls))
		return ;
	ls->tokens = ft_tokens(ls, ls->linefromread);
	if (parseline(ls))
	{
		ft_free(&ls->tokens);
		return ;
	}
	if (count_herdoc(ls->tokens) && itsheredoc(ls))
	{
		ft_free(&ls->tokens);
		return ;
	}
	execution(ls);
	ft_free(&ls->tokens);
}
