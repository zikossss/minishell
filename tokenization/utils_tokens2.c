/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:49:09 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:57:40 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	normal_word_alloc(int len, char **string, int *i, char *f)
{
	string[(*i)] = malloc(sizeof(char) * (len + 1));
	if (!string[(*i)])
		return (ftfree(*i, (void ***)&string));
	ft_strnncpy(string[(*i)], f, len);
	(*i)++;
	return (0);
}

int	insidequotesalloc(char *f, int *j, char **string, int *i)
{
	int	start;
	int	len;

	start = (*j);
	skippinside(f, f[*j], j);
	while (f[*j] && !ft_strchar("><| ", f[*j]))
		(*j)++;
	len = (*j);
	string[(*i)] = malloc(sizeof(char) * ((len - start) + 1));
	if (!string[(*i)])
		return (ftfree(*i, (void ***)&string));
	ft_strnncpy(string[(*i)], f + start, ((len - start)));
	(*i)++;
	return (0);
}

int	alloc_and_copy_for_operator(char **string, int *i, char *f, int *j)
{
	string[(*i)] = malloc(sizeof(char) * 2);
	if (!string[(*i)])
		return (ftfree(*i, (void ***)&string));
	ft_strnncpy(string[(*i)], f + (*j), 1);
	return (0);
}

void	count_operator(char *f, int *j, int *count)
{
	char	c;

	c = f[*j];
	while (f[(*j) + 1] && f[(*j) + 1] == c)
	{
		(*count)++;
		(*j)++;
	}
	(*j) -= (*count) - 1;
}

int	ftfree(int i, void ***string)
{
	if (!i || !string || !*string)
		return (1);
	while (i > 0)
	{
		i--;
		if ((*string)[i])
		{
			free((*string)[i]);
			(*string)[i] = NULL;
		}
	}
	free(*string);
	(*string) = NULL;
	return (1);
}
