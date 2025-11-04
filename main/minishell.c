/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:41:34 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:46:55 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_var_for_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_mini	*ls;

	if (ac != 1)
		return (1);
	(void)av;
	ls = malloc(sizeof(t_mini));
	if (!ls)
		return (1);
	init_struct(ls);
	while (1)
	{
		recievesignals();
		ls->linefromread = getinput("minishell>$ ");
		if (!ls->linefromread)
			my_exit(ls);
		if (ls->linefromread[0] == '\0' || !ft_isspaces(ls->linefromread))
		{
			free(ls->linefromread);
			continue ;
		}
		add_history(ls->linefromread);
		run_program(ls, envp);
		free(ls->linefromread);
	}
	return (0);
}
