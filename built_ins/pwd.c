/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:55:39 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 18:45:41 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_mini *ls)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (!str)
		str = ft_strdup(ls->newpwd);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	free(str);
	ls->stat = 0;
}
