/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:53:06 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 01:53:34 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parce_new_line(char *line, char *new_line, int i, int j)
{
	char	c;

	c = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
			i++;
			continue ;
		}
		if (line[i])
			new_line[j] = line[i];
		else
			continue ;
		j++;
		i++;
	}
	new_line[j] = '\0';
}

char	*parse_line(char *line)
{
	char	*new_line;
	int		x;
	int		xquote;

	x = ft_strlen(line);
	xquote = countquote(line);
	if (!there_is_quotes(line))
	{
		x -= xquote;
		new_line = malloc(sizeof(char) * (x + 1));
		if (!new_line)
			return (NULL);
		parce_new_line(line, new_line, 0, 0);
		free(line);
		return (new_line);
	}
	return (line);
}

void	addvalid_arg(t_mini *ls, int index)
{
	char	**str;

	while (ls->commands[index])
	{
		if (ft_isnumber(ls->commands[index][0])
			|| is_valide_var(ls->commands[index]))
		{
			ls->stat = 1;
			ft_str_error(ls, ": not a valid identifier\n", ls->commands[index]);
			index++;
			continue ;
		}
		str = new_env(ls->commands[index], ls);
		ls->exportenv = str;
		index++;
	}
}

void	print_export(t_mini *ls, int index)
{
	char	*str;
	char	*str1;
	int		i;

	i = 0;
	if (!ls->commands[index])
	{
		while (ls->exportenv[i])
		{
			str1 = ft_strdup1(ls->exportenv[i]);
			protect_malloc(ls, str1);
			str = ft_strjoin(DEC, str1);
			free(str1);
			protect_malloc(ls, str);
			ft_putstr_fd(str, ls->fd);
			ft_putstr_fd("\n", ls->fd);
			free(str);
			i++;
		}
	}
}

void	export(t_mini *ls, int *index)
{
	(*index)++;
	if (ls->commands[*index] && !ls->xpipe)
	{
		addvalid_arg(ls, *index);
		ft_free(&ls->env);
		ls->env = copy_env(ls, ls->exportenv);
	}
	else
		print_export(ls, *index);
}
