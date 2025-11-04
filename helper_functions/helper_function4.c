/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:32:27 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 18:41:43 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	p = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				if (str[i + j + 1] == ' ')
					i++;
				return (str + i + ft_strlen(to_find));
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		dl;
	int		sl;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dl = ft_strlen(s1);
	sl = ft_strlen(s2);
	str = malloc(sizeof(char) * (dl + sl + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	while (s2[i])
	{
		str[i + dl] = s2[i];
		i++;
	}
	str[i + dl] = '\0';
	return (str);
}

char	*ft_join_var_exp(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		dl;
	int		sl;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dl = ft_strlen(s1);
	sl = ft_strlen(s2);
	str = malloc(sizeof(char) * (dl + sl + 2));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	while (s2[i])
	{
		str[i + dl] = s2[i];
		i++;
	}
	str[i + dl] = ' ';
	str[i + dl + 1] = '\0';
	return (str);
}
