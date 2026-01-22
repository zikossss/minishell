/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:24:58 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/16 21:45:01 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*takevalue(t_mini *ls, char *varname, int n)
{
	int		len;
	char	*varvalue;

	len = ft_strlen(varname);
	varvalue = malloc(sizeof(char) * ((len - n) + 1));
	protect_malloc(ls, varvalue);
	ft_strnncpy(varvalue, varname + n, (len - n));
	return (varvalue);
}

char	*findvar(t_mini *ls, char *nameofvar)
{
	char	*varvalue;
	int		i;
	int		j;

	i = -1;
	while (ls->env[++i])
	{
		j = 0;
		while (ls->env[i][j] && ls->env[i][j] != '=')
			j++;
		if (!ft_strncmp(ls->env[i], nameofvar, j) && nameofvar[j] == '\0')
		{
			varvalue = takevalue(ls, ls->env[i], j + 1);
			if ((cowntswords(varvalue, ' ') != 1) && (ls->outfile
					|| ls->infile))
			{
				free(varvalue);
				ls->isambiguous = 1;
				return (NULL);
			}
			return (varvalue);
		}
	}
	return (NULL);
}

char	*getvarname(t_mini *ls, char *line, int j)
{
	char	*name;
	int		i;

	i = 0;
	while (line[j + 1 + i] && is_validchar(line[j + 1 + i]))
		i++;
	name = malloc(sizeof(char) * (i + 1));
	protect_malloc(ls, name);
	ft_strnncpy(name, line + (j + 1), i);
	return (name);
}

char	*replace_it(char *line, int *j, char *varvalue, char *nameofvar)
{
	char	*editedinput;
	int		len;

	len = 0;
	editedinput = malloc(sizeof(char) * ((*j) + 1));
	if (!editedinput)
		return (free(nameofvar), free(varvalue), NULL);
	ft_strnncpy(editedinput, line, *j);
	len = ((*j) + ft_strlen(nameofvar) + 1);
	editedinput = ft_joinofvar(editedinput, varvalue);
	if (!editedinput)
		return (free(nameofvar), free(varvalue), NULL);
	if (editedinput[0])
		(*j) = ft_strlen(editedinput) - 1;
	editedinput = ft_joinofvar(editedinput, (line + len));
	if (!editedinput)
		return (free(nameofvar), free(varvalue), NULL);
	free(nameofvar);
	free(varvalue);
	return (editedinput);
}

char	*replacevar(t_mini *ls, char *line, int *j)
{
	char	*nameofvar;
	char	*varvalue;
	char	*editedinput;

	nameofvar = getvarname(ls, line, *j);
	if (!ft_strcmp(nameofvar, "PWD") && ls->newpwd)
	{
		varvalue = ft_strdup(ls->newpwd);
		protect_malloc(ls, varvalue);
	}
	else if (line[(*j) + 1] && line[(*j) + 1] == '?')
	{
		varvalue = ft_itoa(ls->stat);
		protect_malloc(ls, varvalue);
		free(nameofvar);
		nameofvar = ft_strdup("?");
		protect_malloc(ls, nameofvar);
	}
	else
		varvalue = findvar(ls, nameofvar);
	if (!varvalue)
		return (free(nameofvar), NULL);
	editedinput = replace_it(line, j, varvalue, nameofvar);
	protect_malloc(ls, editedinput);
	return (editedinput);
}
