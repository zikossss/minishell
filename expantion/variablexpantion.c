/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variablexpantion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:24:23 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/16 00:36:38 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	treatdquotesvar(t_mini *ls, int *i, int *j, char **commands)
{
	int		x;
	char	*tmp;

	x = *j;
	(*j)++;
	treat_it_with_dquote(ls, i, j, commands);
	tmp = create_substr_dq(commands, x, j, *i);
	protect_malloc(ls, tmp);
	commands[*i] = tmp;
	ls->isambiguous = 0;
}

void	treat_normal(t_mini *ls, int *i, int *j, char **commands)
{
	char	*newinput;

	newinput = replacevar(ls, commands[*i], j);
	if (!newinput && ls->isambiguous)
	{
		(*j)++;
		return ;
	}
	if (newinput)
	{
		free(commands[*i]);
		commands[*i] = newinput;
	}
	else if (is_validchar(commands[*i][*j + 1]))
	{
		commands[*i] = update_var(ls, *j, *i, commands);
	}
	if (commands[*i][*j])
		(*j)++;
}

void	treatnormalvar(t_mini *ls, int *i, int *j, char **commands)
{
	int	f;

	f = 0;
	ls->expand = 1;
	while (commands[f] && ls->heredoc != 4)
	{
		if (!ft_strcmp(commands[f], "export"))
			ls->expand = 0;
		f++;
	}
	treat_normal(ls, i, j, commands);
}

void	no_treat(t_mini *ls, char **command, int i, int *j)
{
	char	*str;

	str = malloc(sizeof(char) * ((ft_strlen(command[i]) - 2) + 1));
	protect_malloc(ls, str);
	command[i] = create_substr(command[i], str, j);
}

void	variablexpantion(t_mini *ls, char **commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			isredirection(ls, i);
			if (commands[i][j] == 39 && ls->heredoc != 4)
				no_treat(ls, commands, i, &j);
			else if (commands[i][j] == 34 && ls->heredoc != 4)
				treatdquotesvar(ls, &i, &j, commands);
			else if (commands[i][j] == '$')
				treatnormalvar(ls, &i, &j, commands);
			else
				j++;
		}
		if (ls->heredoc == 4)
			break ;
		i++;
	}
	resplit_tokens(ls, commands);
}
