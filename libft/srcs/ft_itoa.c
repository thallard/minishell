/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:28:43 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:55:08 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_nbr(char **res, size_t nbr, int rang)
{
	if (nbr < 10)
		(*res)[rang] = nbr + '0';
	else
	{
		ft_fill_nbr(res, nbr % 10, rang);
		ft_fill_nbr(res, nbr / 10, rang - 1);
	}
}

static char	*ft_itoa_0a9(int n)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * 2)))
		return (NULL);
	res[0] = n + '0';
	res[1] = '\0';
	return (res);
}

static long	ft_abs_long(int n)
{
	long	nbr;

	nbr = (long)n;
	if (nbr >= 0)
		return (nbr);
	return (-nbr);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	compteur;
	long	nbr;

	if (n >= 0 && n <= 9)
		return (ft_itoa_0a9(n));
	len = 1;
	compteur = 1;
	if (n < 0)
		len++;
	nbr = ft_abs_long(n);
	while (compteur <= nbr)
	{
		compteur = compteur * 10;
		len++;
	}
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	ft_fill_nbr(&res, nbr, len - 2);
	res[len - 1] = '\0';
	if (n < 0)
		res[0] = '-';
	return (res);
}
