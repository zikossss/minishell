/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:49:04 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 21:38:48 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skippinside(char *s, char c, int *i)
{
	if (!s || !i || *i < 0)
		return ;
	if (!s[*i])
		return ;
	if (s[(*i)] == c && s[(*i) + 1] && s[(*i) + 1] == c)
	{
		(*i) += 2;
		return ;
	}
	(*i)++;
	while (s[(*i)] && s[(*i)] != c)
		(*i)++;
	if (s[(*i)] == c)
		(*i)++;
}

void	countoperator(char *s, int *j)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			skippinside(s, s[i], &i);
		else if (ft_strchar("><|", s[i]))
		{
			(*j)++;
			c = s[i];
			while (s[i] == c)
				i++;
		}
		else
			i++;
	}
}

void	ftskipxcount(char *s, char c, int *i, int *j)
{
	if (!s || !i || !j || *i < 0)
		return ;
	if (s[(*i)] && s[(*i)] == c && s[(*i) + 1] && s[(*i) + 1] == c)
	{
		(*i) += 2;
		(*j)++;
		return ;
	}
	(*i)++;
	while (s[(*i)] && s[(*i)] != c)
	{
		if (s[(*i) + 1] && s[(*i) + 1] == c)
			(*j)++;
		(*i)++;
	}
	if (s[(*i)] == c)
		(*i)++;
}

void	no_operator_skip(char *s, int *i)
{
	while (s[*i] && !ft_strchar("><| ", s[*i]))
	{
		if (s[*i] == 34 || s[*i] == 39)
			skippinside(s, s[*i], i);
		else
			(*i)++;
	}
}

int	cowntword(char *s)
{
	int	i;
	int	j;

	if (!s || !*s)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_strchar("><| ", s[i]))
		{
			if (i == 0 || (i > 0 && ft_strchar("><| ", s[i - 1])))
			{
				if (s[i] == 34 || s[i] == 39)
					ftskipxcount(s, s[i], &i, &j);
				else
					j++;
			}
			no_operator_skip(s, &i);
		}
		else
			i++;
	}
	countoperator(s, &j);
	return (j);
}
