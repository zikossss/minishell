/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:25:08 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 17:22:39 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_substr_dq(char **line, int x, int *j, int i)
{
	int		f;
	int		c;
	char	*str;

	f = x;
	c = 0;
	str = malloc(sizeof(char) * ((ft_strlen(line[i]) - 2) + 1));
	if (!str)
		return (NULL);
	ft_strnncpy(str, line[i], x);
	if (line[i][f] == 34)
		f++;
	while (line[i][f])
	{
		if (line[i][f] == 34 && !c)
		{
			c = 1;
			(*j) = x;
			f++;
			continue ;
		}
		str[x++] = line[i][f++];
	}
	str[x] = '\0';
	return (free(line[i]), str);
}

int	is_validchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	**join_and_split(t_mini *ls, char **commands)
{
	int		i;
	char	*new_arr;
	char	*old_arr;
	char	**new_commands;

	i = 0;
	new_arr = malloc(1);
	protect_malloc(ls, new_arr);
	new_arr[0] = '\0';
	while (commands[i])
	{
		old_arr = new_arr;
		new_arr = ft_join_var_exp(new_arr, commands[i]);
		free(old_arr);
		protect_malloc(ls, new_arr);
		i++;
	}
	new_commands = ft_split(new_arr, ' ');
	free(new_arr);
	protect_malloc(ls, new_commands);
	return (new_commands);
}

int	check_only_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] != 39 && str[i] != 34)
			return (1);
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			if (str[i + 1] && str[i + 1] != c)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*create_substr(char *line, char *substr, int *j)
{
	int	c;
	int	x;
	int	i;

	x = 0;
	c = 0;
	i = (*j);
	ft_strnncpy(substr, line, i);
	x = i;
	if (line[i] == 39)
		i++;
	while (line[i])
	{
		if (line[i] == 39 && !c)
		{
			c = 1;
			i++;
			(*j) = x;
			continue ;
		}
		substr[x++] = line[i++];
	}
	substr[x] = '\0';
	free(line);
	return (substr);
}
