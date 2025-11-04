/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:39:06 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:41:06 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_handler(t_mini *ls, char *line, char *delimiter)
{
	int	fd;

	if (line)
		free(line);
	close(ls->heredocfd);
	free(delimiter);
	reset_sihandler();
	if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
	{
		fd = open("/dev/tty", O_RDONLY);
		protect_syscall(fd);
	}
	ls->stat = 130;
	return (1);
}

int	aretheyoption(t_mini *ls)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	ls->cn_flag = 1;
	while (ls->commands[++i])
	{
		if (isredirection(ls, i) && ls->commands[i + 1])
			i++;
		else if (x == 0 && isaccesiblecommand(ls, i))
		{
			ft_free(&ls->path);
			x = 1;
		}
		else if (!isredirection(ls, i) && (ft_strncmp(ls->commands[i], "-", 1)
				&& ft_strncmp(ls->commands[i], "|", 1)))
		{
			if (isaccesiblecommand(ls, i))
				ft_free(&ls->path);
			else
				return (1);
		}
	}
	return (0);
}

int	size_to_alloc(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	c = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !c)
			c = str[i];
		else if (str[i] && c == str[i])
			c = 0;
		else
			count++;
		i++;
	}
	return (count);
}

char	*correct_heredoc(t_mini *ls, char *limiter)
{
	char	*line;
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = 0;
	line = malloc(sizeof(char) * (size_to_alloc(limiter) + 1));
	protect_malloc(ls, line);
	while (limiter[i])
	{
		if ((limiter[i] == '\'' || limiter[i] == '\"') && !c)
			c = limiter[i++];
		if (limiter[i] && c == limiter[i])
			c = 0;
		else
			line[j++] = limiter[i];
		i++;
	}
	line[j] = '\0';
	return (line);
}
