/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:47:53 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:47:54 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	amoperator(t_mini *ls, char *token, char *nexttoken)
{
	if ((ft_strchar("<>|", token[0])) && !ft_strcmp(nexttoken, "|"))
		return (ft_str_error(ls, ": syntax error near unexpected token\n",
				token), 1);
	if (!ft_strcmp(token, "|") && !ft_strcmp(nexttoken, "|"))
		return (ft_str_error(ls, ": syntax error near unexpected token\n",
				token), 1);
	if ((ft_strchar("<>|", token[0])) && !nexttoken)
		return (ft_str_error(ls, ": syntax error near unexpected token\n",
				token), 1);
	if ((ft_strchar("<>", token[0])) && ft_strchar("<>", nexttoken[0]))
		return (ft_str_error(ls, ": syntax error near unexpected token\n",
				token), 1);
	return (0);
}

int	parseline(t_mini *ls)
{
	int	i;

	i = 0;
	if ((ft_strchar("|", ls->tokens[0][0])))
	{
		ls->stat = 2;
		return (ft_str_error(ls, ": syntax error near unexpected token\n",
				ls->tokens[i]), 1);
	}
	while (ls->tokens[i])
	{
		if (amoperator(ls, ls->tokens[i], ls->tokens[i + 1]))
		{
			ls->stat = 2;
			return (1);
		}
		i++;
	}
	return (0);
}
