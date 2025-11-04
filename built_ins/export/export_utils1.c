/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:53:56 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 01:54:25 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calculate_size(char *s)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (s[i])
	{
		if (s[i] == '=')
			d++;
		i++;
	}
	if (d > 0 && there_is_quotes_ex(s))
		return (i + 3);
	else
		return (i + 1);
}

void	copy_and_quote(char *s, char *p)
{
	int	i;
	int	j;
	int	quote_added;

	i = 0;
	j = 0;
	quote_added = 0;
	while (s[i])
	{
		p[j++] = s[i];
		if (!quote_added && s[i] == '=' && there_is_quotes_ex(s))
		{
			p[j++] = '"';
			quote_added = 1;
		}
		i++;
	}
	if (quote_added)
		p[j++] = '"';
	p[j] = '\0';
}

char	*ft_strdup1(char *s)
{
	char	*p;
	int		size;

	size = calculate_size(s);
	p = malloc(sizeof(char) * size);
	if (!p)
		return (NULL);
	copy_and_quote(s, p);
	return (p);
}

int	replace_env(t_mini *ls, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ls->exportenv[i])
	{
		if (!ft_strncmp(ls->exportenv[i], line, find_equal(line)))
		{
			tmp = ft_strdup(line);
			protect_malloc(ls, tmp);
			free(ls->exportenv[i]);
			ls->exportenv[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**add_new_env(t_mini *ls, char *line)
{
	int		i;
	char	**array;

	i = 0;
	if (replace_env(ls, line))
		return (NULL);
	array = malloc(sizeof(char *) * (ft_str_count(ls) + 2));
	protect_malloc(ls, array);
	while (ls->exportenv[i])
	{
		array[i] = ft_strdup(ls->exportenv[i]);
		clean_up(ls, i, (void ***)&array);
		i++;
	}
	array[i] = ft_strdup(line);
	clean_up(ls, i, (void ***)&array);
	array[i + 1] = NULL;
	return (array);
}
