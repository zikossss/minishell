/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:55:19 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 21:23:35 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n_arg_r(t_mini *ls, int j)
{
	int	i;

	i = 0;
	while (ls->commands[j] && ls->commands[j][i])
	{
		if (ls->commands[j][i] && (ls->commands[j][i] == '+'
				|| ls->commands[j][i] == '-'))
			i++;
		if (ls->commands[j][i] && !ft_isnumber(ls->commands[j][i]))
		{
			ls->stat = 2;
			ft_str_error(ls, ": numeric argument required\n", ls->commands[j]);
			return (1);
		}
		if (ls->commands[j][i])
			i++;
	}
	return (0);
}

int	check_arguments(t_mini *ls)
{
	int	j;

	j = 1;
	if (ls->commands && check_to_many_args(ls) >= 1)
	{
		if (check_n_arg_r(ls, j))
			return (0);
		if (check_to_many_args(ls) > 2)
			return (ft_str_error(ls, ": too many arguments\n", ls->commands[0]),
				ls->stat = 1);
		if (ft_atoi(ls->commands[j]) != -1)
		{
			ls->stat = ft_atoi(ls->commands[j]);
			ls->stat = ls->stat % 256;
			if (ls->stat < 0)
				ls->stat += 256;
		}
	}
	return (0);
}

void	free_befor_exit(t_mini *ls)
{
	if (ls->pipefd)
		ft_freepipe(ls);
	if (ls->env)
		ft_free(&ls->env);
	if (ls->exportenv)
		ft_free(&ls->exportenv);
	if (ls->tokens)
		ft_free(&ls->tokens);
	if (ls->commands)
		ft_free(&ls->commands);
	if (ls->oldpwd)
		free(ls->oldpwd);
	if (ls->newpwd)
		free(ls->newpwd);
	if (ls->linefromread)
		free(ls->linefromread);
	if (ls)
		free(ls);
}

void	my_exit(t_mini *ls)
{
	int	stat;

	ft_putstr_fd("exit\n", 1);
	if (ls->commands && !ft_strcmp(ls->commands[0], "exit"))
	{
		if (check_arguments(ls))
			return ;
	}
	stat = ls->stat;
	free_befor_exit(ls);
	exit(stat);
}
