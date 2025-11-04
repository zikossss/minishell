/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:39:14 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:47:01 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_herdoc(t_mini *ls, char *line, char *cor_limetter)
{
	while (1)
	{
		line = getinput("HEREDOC>");
		if (g_var_for_signal == SIGINT)
			return (heredoc_handler(ls, line, cor_limetter));
		if (!line)
		{
			ft_str_error(ls,
				" :warning: here-document delimited by end-of-file\n",
				cor_limetter);
			break ;
		}
		if (!ft_strcmp(cor_limetter, line))
			break ;
		if (!toexpand(ls))
			variablexpantion(ls, &line);
		ft_putstr_fd(line, ls->heredocfd);
		ft_putstr_fd("\n", ls->heredocfd);
		free(line);
	}
	free(line);
	return (0);
}

int	fileforheredoc(t_mini *ls)
{
	char	*c;
	int		*buffer;
	int		fd;
	int		x;

	x = 0;
	buffer = malloc(sizeof(int));
	protect_malloc(ls, buffer);
	fd = open("/dev/random", O_RDONLY);
	if (protect_syscall(fd))
		return (1);
	x = read(fd, buffer, 4);
	if (protect_syscall(x))
		return (1);
	close(fd);
	c = ft_itoa(*buffer);
	protect_malloc(ls, c);
	ls->file = ft_strjoin("/tmp/", c);
	free(buffer);
	free(c);
	protect_malloc(ls, ls->file);
	ls->heredocfd = open(ls->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (protect_syscall(ls->heredocfd))
		return (1);
	return (0);
}

int	doheredoc(t_mini *ls)
{
	char	*line;
	char	*cor_limiter;

	line = NULL;
	if (fileforheredoc(ls))
		return (1);
	cor_limiter = correct_heredoc(ls, ls->heredocdelimiter);
	heredoc_signal();
	if (run_herdoc(ls, line, cor_limiter))
		return (1);
	close(ls->heredocfd);
	free(cor_limiter);
	return (0);
}

int	begin_herdoc(t_mini *ls, int x, int i)
{
	ls->heredoc = 4;
	ls->heredocdelimiter = ls->commands[i + 1];
	ls->okay = aretheyoption(ls);
	if (doheredoc(ls))
	{
		free(ls->file);
		return (ftfree(x, (void ***)&ls->files), ls->commands = NULL, 1);
	}
	ls->files[x] = ls->file;
	if (!ls->files[x])
		my_exit(ls);
	return (0);
}

int	itsheredoc(t_mini *ls)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	ls->commands = ls->tokens;
	ls->files = malloc(sizeof(char *) * (count_herdoc(ls->commands) + 1));
	protect_malloc(ls, ls->files);
	while (ls->commands[i])
	{
		if (isredirection(ls, i) == 4 && ls->commands[i + 1])
		{
			if (begin_herdoc(ls, x, i))
				return (1);
			x++;
		}
		i++;
	}
	ls->files[x] = NULL;
	ls->commands = NULL;
	return (0);
}
