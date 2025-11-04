/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:55:01 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 01:55:02 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_env(char *line, t_mini *ls)
{
	char	**arr;

	arr = add_new_env(ls, line);
	if (arr)
	{
		ft_free(&ls->exportenv);
		return (arr);
	}
	return (ls->exportenv);
}

int	countquote(char *line)
{
	int		i;
	int		x;
	char	c;

	i = 0;
	x = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			c = line[i];
			x++;
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		i++;
	}
	return (x);
}
