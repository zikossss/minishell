/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:26:25 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:26:26 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isclose(t_mini *ls)
{
	int	i;

	i = 0;
	while (ls->linefromread[i])
	{
		if (ls->linefromread[i] == 34 || ls->linefromread[i] == 39)
		{
			if (!checkquoteclosed(ls->linefromread, &i, ls->linefromread[i]))
			{
				printf("line is not valid : quote not closed\n");
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	thereispipe(t_mini *ls)
{
	int	i;

	i = 0;
	while (ls->commands[i])
	{
		if (!ft_strcmp(ls->commands[i], "|"))
			return (i);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	isbuiltin(char *arg)
{
	if (!ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

void	dobuiltin(t_mini *ls, int *index)
{
	if (!ft_strcmp(ls->commands[*index], "echo"))
		echo(ls, index);
	else if (!ft_strcmp(ls->commands[*index], "cd"))
		cd(ls, index);
	else if (!ft_strcmp(ls->commands[*index], "pwd"))
		pwd(ls);
	else if (!ft_strcmp(ls->commands[*index], "export"))
		export(ls, index);
	else if (!ft_strcmp(ls->commands[*index], "unset"))
		unset(ls, index);
	else if (!ft_strcmp(ls->commands[*index], "env"))
		env(ls);
	else if (!ft_strcmp(ls->commands[*index], "exit"))
		my_exit(ls);
}
