/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:54:39 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 01:54:47 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_str_count(t_mini *ls)
{
	int	i;

	i = 0;
	while (ls->exportenv[i])
		i++;
	return (i);
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	there_is_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			return (0);
		s++;
	}
	return (1);
}

int	there_is_quotes_ex(char *s)
{
	while (*s)
	{
		if (*s == '\"')
			return (0);
		s++;
	}
	return (1);
}

int	is_valide_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[0] == '=')
			return (1);
		if (s[i] != '=' && !is_validchar(s[i]))
		{
			return (1);
		}
		if (s[i] == '=')
			break ;
		i++;
	}
	return (0);
}
