/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:24:45 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:24:46 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	treat_it_with_dquote(t_mini *ls, int *i, int *j, char **commands)
{
	char	*newinput;

	while (commands[*i][*j] && commands[*i][*j] != 34)
	{
		if (commands[*i][*j] == '$' && commands[*i][*j + 1] == 34)
		{
			(*j)++;
			break ;
		}
		if (commands[*i][*j] == '$')
		{
			newinput = replacevar(ls, commands[*i], j);
			if (newinput)
			{
				free(commands[*i]);
				commands[*i] = newinput;
			}
			else if (is_validchar(commands[*i][*j + 1]))
				commands[*i] = update_var(ls, *j, *i, commands);
		}
		if (commands[*i][*j])
			(*j)++;
	}
}

void	resplit_tokens(t_mini *ls, char **commands)
{
	if (ls->expand && ls->heredoc != 4)
	{
		ls->commands = join_and_split(ls, commands);
		ft_free(&commands);
	}
	ls->expand = 0;
}

void	update_it(char **commands, int i, char *varname, char *editedptr)
{
	int	x;
	int	d;

	x = 0;
	d = 0;
	while (commands[i][x])
	{
		if (commands[i][x] == '$')
		{
			x += ft_strlen(varname) + 1;
			continue ;
		}
		editedptr[d] = commands[i][x];
		x++;
		d++;
	}
	editedptr[d] = '\0';
	free(varname);
	free(commands[i]);
}

char	*update_var(t_mini *ls, int j, int i, char **commands)
{
	int		x;
	char	*varname;
	char	*editedptr;

	x = ft_strlen(commands[i]);
	varname = getvarname(ls, commands[i], j);
	editedptr = malloc(sizeof(char) * ((x - ft_strlen(varname) - 1) + 1));
	if (!editedptr)
	{
		free(varname);
		my_exit(ls);
	}
	update_it(commands, i, varname, editedptr);
	return (editedptr);
}
