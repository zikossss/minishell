/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:26:48 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:31:51 by zajabir          ###   ########.fr       */
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

static void	ft_strnnncpy(char *dst, char *src, unsigned int n,
		char *commandname)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '/';
	i++;
	j = 0;
	while (commandname[j])
	{
		dst[i + j] = commandname[j];
		j++;
	}
	dst[i + j] = '\0';
}

static int	cowntwords(char *s, char c)
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

static char	**strrr(char *f, char **string, char c, char *commandname)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (f[j] && i < cowntwords(f, c))
	{
		if (f[j] != c)
		{
			string[i] = malloc(sizeof(char) * (ft_l(f, c, j)
						+ ft_strlen(commandname) + 3));
			if (!string[i])
			{
				ftfree(i, (void ***)&string);
				return (NULL);
			}
			ft_strnnncpy(string[i], f + j, ft_l(f, c, j), commandname);
			i++;
			j += ft_l(f, c, j);
		}
		else
			j++;
	}
	string[i] = NULL;
	return (string);
}

char	**ft_splitpath(char *s, char c, char *commandname)
{
	char	**strings;
	char	*f;

	f = (char *)s;
	strings = malloc(sizeof(char *) * (cowntwords(f, c) + 1));
	if (!strings)
		return (NULL);
	return (strrr(f, strings, c, commandname));
}
