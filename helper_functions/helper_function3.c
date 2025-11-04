/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:32:15 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:32:16 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_l(char *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] && s[j] != c)
	{
		i++;
		j++;
	}
	return (i);
}

static void	ft_strnnncpy(char *dst, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	cowntswords(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static char	**strrr(char *f, char **string, char c, int i)
{
	int	j;

	j = 0;
	while (f[j] && i < cowntswords(f, c))
	{
		if (f[j] != c)
		{
			string[i] = malloc(sizeof(char) * (ft_l(f, c, j) + 2));
			if (!string[i])
			{
				while (i > 0)
					free(string[--i]);
				free(string);
				return (NULL);
			}
			ft_strnnncpy(string[i], f + j, ft_l(f, c, j));
			i++;
			j += ft_l(f, c, j);
		}
		else
			j++;
	}
	string[i] = NULL;
	return (string);
}

char	**ft_split(char *s, char c)
{
	char	**strings;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	strings = malloc(sizeof(char *) * (cowntswords(s, c) + 1));
	if (!strings)
		return (NULL);
	return (strrr(s, strings, c, i));
}
