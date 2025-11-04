/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:41:49 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:46:20 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_str_error(t_mini *ls, char *str, char *arg)
{
	int		i;
	char	*mssg_error;
	char	*tmp;

	if (!str || !arg)
		return ;
	i = ft_strlen("Minishell: ") + ft_strlen(arg) + ft_strlen(str);
	mssg_error = malloc(i + 1);
	protect_malloc(ls, mssg_error);
	ft_strcpy(mssg_error, "Minishell: ");
	tmp = ft_strjoin(mssg_error, arg);
	free(mssg_error);
	protect_malloc(ls, tmp);
	mssg_error = ft_strjoin(tmp, str);
	free(tmp);
	protect_malloc(ls, mssg_error);
	write(STDERR_FILENO, mssg_error, ft_strlen(mssg_error));
	free(mssg_error);
}

char	*getinput(char *str)
{
	char	*line;

	line = readline(str);
	if (!line)
		return (NULL);
	return (line);
}

int	ft_isspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
			return (1);
		i++;
	}
	return (0);
}

void	reinit(t_mini *ls)
{
	g_var_for_signal = 0;
	ls->pipefd = NULL;
	ls->fd = 1;
	ls->okay = 0;
	ls->xpipe = 0;
	ls->infile = 0;
	ls->outfile = 0;
	ls->heredoc = 0;
	ls->infd = 0;
	ls->compos = 0;
	ls->isbuiltin = 0;
	ls->inflag = 0;
	ls->outflag = 0;
	ls->heredocfd = 0;
	ls->isambiguous = 0;
	ls->pid = 0;
	ls->v = 0;
}

void	run_program(t_mini *ls, char **envp)
{
	if (g_var_for_signal == SIGINT)
		ls->stat = 130;
	if (!ls->start)
	{
		ls->start = 1;
		ls->exportenv = copy_env(ls, envp);
		ls->env = copy_env(ls, ls->exportenv);
	}
	begin_work(ls);
	reinit(ls);
}
