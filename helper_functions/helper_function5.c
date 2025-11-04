/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:33:05 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 16:59:00 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

char	*ft_joinofvar(char *s1, char *s2)
{
	int		fl;
	int		i;
	char	*ptr;

	if (!s2)
		return (free(s1), NULL);
	fl = ft_strlen(s1);
	ptr = malloc(sizeof(char) * ((ft_strlen(s2) + fl) + 1));
	if (!ptr)
		return (free(s1), NULL);
	ft_strcpy(ptr, s1);
	free(s1);
	i = 0;
	while (s2[i])
	{
		ptr[fl + i] = s2[i];
		i++;
	}
	ptr[fl + i] = '\0';
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isalnum(int c)
{
	if (ft_isnumber(c) || ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}

void	ft_strnncpy(char *dst, char *src, unsigned int n)
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
