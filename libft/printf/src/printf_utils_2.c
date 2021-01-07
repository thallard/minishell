/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:34:52 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 10:29:15 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_atoi_simplify(va_list ap, char **str)
{
	int	res;
	int	signe;

	res = 0;
	signe = 1;
	if (**str == '0' || **str == '-' || **str == '.')
		(*str)++;
	while (**str == ' ')
	{
		(*str)++;
		signe = -1;
	}
	if (**str == '*')
	{
		res = va_arg(ap, int);
		(*str)++;
		return (res * signe);
	}
	while (**str >= '0' && **str <= '9')
		res = 10 * res + (*(*str)++ - '0');
	return (res * signe);
}

int	ft_putspace(int nb, int fd)
{
	char	c;
	int		i;
	char	*buffer;

	c = ' ';
	i = -1;
	if (!(buffer = malloc(nb)))
		return (-1);
	while (++i < nb)
		buffer[i] = c;
	write(fd, buffer, nb);
	free(buffer);
	return (nb);
}

int	ft_putzero(int nb, int fd)
{
	char	c;
	int		i;
	char	*buffer;

	c = '0';
	i = -1;
	if (!(buffer = malloc(nb)))
		return (-1);
	while (++i < nb)
		buffer[i] = c;
	write(fd, buffer, nb);
	free(buffer);
	return (nb);
}

int	ft_put_zero_and_space(long long i, int *tab, int len, int fd)
{
	int nb_zero;
	int nb_space;
	int nb;
	int diff_sign;

	nb = 0;
	diff_sign = 0;
	nb_zero = ft_max_printf(tab[0] - len, 0);
	if (i < 0 && tab[2] > 0)
		diff_sign = 1;
	nb_space = ft_max_printf(tab[4] - len, 0);
	if (tab[2] >= 0)
	{
		nb_zero = ft_max_printf(tab[2] - (len - diff_sign), 0);
		if (len <= tab[2])
			nb_space = ft_max_printf(ft_max_printf(tab[0],
									tab[4]) - tab[2] - diff_sign, 0);
		else
			nb_space = ft_max_printf(ft_max_printf(tab[0], tab[4]) - len, 0);
	}
	nb += ft_putspace(nb_space, fd);
	if (i < 0 && (tab[0] > 0 || tab[2] > 0))
		nb += ft_put_sign_fd(fd);
	nb += ft_putzero(nb_zero, fd);
	return (nb);
}

int	ft_put_zero_and_space_add(int *tab, int len, int fd)
{
	int nb_zero;
	int nb_space;

	nb_space = ft_max_printf(ft_max_printf(tab[0], tab[4]) - len - 2, 0);
	nb_zero = 0;
	if (tab[2] >= 0)
	{
		nb_zero = ft_max_printf(tab[2] - len, 0);
		if (tab[0] > tab[2])
			nb_space = ft_max_printf(tab[0] - (nb_zero + len + 2), 0);
		else
			nb_space = ft_max_printf(tab[2] - (nb_zero + len + 2), 0);
	}
	ft_putspace(nb_space, fd);
	ft_putstrn_fd("0x", 2, fd);
	ft_putzero(nb_zero, fd);
	return (nb_space + 2 + nb_zero);
}
