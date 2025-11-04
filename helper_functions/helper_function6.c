/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:35:43 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 03:06:31 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	coulen(int nb)
{
	int	count;

	count = 0;
	if (nb <= 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	ft_isnumber(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*ptr;
	long	nb;

	nb = n;
	size = coulen(nb);
	ptr = malloc(sizeof(char) * size + 1);
	if (!ptr)
		return (NULL);
	ptr[size] = '\0';
	size--;
	if (nb == 0)
		ptr[0] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
	}
	while (nb != 0)
	{
		ptr[size] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
	return (ptr);
}

int	sign_handler(char *str, int sign, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long int	ft_atoi(char *nptr)
{
	int		i;
	int		sign;
	long	result;

	if (!nptr)
		return (-1);
	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' ' || nptr[i] == '\"'
			|| nptr[i] == '\''))
		i++;
	sign = sign_handler(nptr, sign, &i);
	if (nptr[i] && (nptr[i] == '\"' || nptr[i] == '\''))
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return ((long int)(result * sign));
}
