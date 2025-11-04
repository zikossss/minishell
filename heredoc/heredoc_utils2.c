/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:39:18 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:40:31 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	toexpand(t_mini *ls)
{
	if (ft_strchar(ls->heredocdelimiter, '\'')
		|| ft_strchar(ls->heredocdelimiter, '\"'))
		return (1);
	return (0);
}

int	protect_syscall(int fd)
{
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

int	count_herdoc(char **tokens)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<<"))
			x++;
		i++;
	}
	return (x);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
