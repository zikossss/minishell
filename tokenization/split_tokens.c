/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:48:52 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:57:57 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operatoralloc(char *f, int *j, char **string, int *i)
{
	int	count;

	while (f[*j] && ft_strchar("><|", f[*j]))
	{
		count = 1;
		count_operator(f, j, &count);
		if (count >= 2)
		{
			string[(*i)] = malloc(sizeof(char) * (count + 1));
			if (!string[(*i)])
				return (ftfree(*i, (void ***)&string));
			ft_strnncpy(string[(*i)], f + (*j), count);
			(*i)++;
			(*j) += count;
			continue ;
		}
		if (alloc_and_copy_for_operator(string, i, f, j))
			return (1);
		if (!f[*j])
			break ;
		(*i)++;
		(*j)++;
	}
	return (0);
}

int	wordalloc(char *f, int *j, char **string, int *i)
{
	int	start;
	int	len;

	start = (*j);
	len = 0;
	if (*j > 0 && f[(*j) - 1] == ' ' && (f[(*j)] == 34 || f[(*j)] == 39))
	{
		if (insidequotesalloc(f, j, string, i))
			return (1);
		else
			return (0);
	}
	else
	{
		while (f[*j] && !ft_strchar("><| ", f[*j]))
		{
			if (f[*j] == 34 || f[*j] == 39)
				skippinside(f, f[*j], j);
			else
				(*j)++;
		}
	}
	len = (*j) - start;
	return (normal_word_alloc(len, string, i, f + start));
}

char	**str(char *f, char **string, int i, int x)
{
	int	j;

	j = 0;
	while (f[j] && i < x)
	{
		if (ft_strchar("><|", f[j]))
		{
			if (operatoralloc(f, &j, string, &i))
				return (NULL);
		}
		else if (f[j] != ' ')
		{
			if (wordalloc(f, &j, string, &i))
				return (NULL);
		}
		else
			j++;
	}
	string[i] = NULL;
	return (string);
}

char	**ft_tokens(t_mini *ls, char *f)
{
	char	**strings;
	char	**tokens;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!f)
		return (NULL);
	x = cowntword(f);
	strings = malloc(sizeof(char *) * (x + 1));
	protect_malloc(ls, strings);
	tokens = str(f, strings, i, x);
	protect_malloc(ls, tokens);
	return (tokens);
}
