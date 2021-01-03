/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_type_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:54:11 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:46:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	str_int(va_list ap, int *nb_char, int *tab)
{
	long int	i;
	int			len;
	int			nb;

	nb = 0;
	i = va_arg(ap, int);
	len = ft_nbrlen_base(i, 10);
	nb += ft_put_zero_and_space(i, tab, len, STDOUT);
	if (i < 0 && (tab[0] > 0 || tab[2] > 0))
		i *= -1;
	nb += ft_putnbrn_fd(i, tab, STDOUT);
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), STDOUT);
	*nb_char += nb;
}

void	str_char(va_list ap, int *nb_char, int *tab)
{
	int	i;
	int	nb;

	nb = 0;
	i = va_arg(ap, int);
	nb += ft_putchar_and_space_fd(tab, i, STDOUT);
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), STDOUT);
	*nb_char += nb;
}

void	str_string(va_list ap, int *nb_char, int *tab)
{
	char	*s;
	int		nb;

	nb = 0;
	s = va_arg(ap, char*);
	nb += ft_putstr_and_space_fd(tab, s, STDOUT);
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), STDOUT);
	*nb_char += nb;
}

void	str_percent(int *nb_char, int *tab)
{
	int	nb;

	nb = 0;
	nb += ft_putchar_and_space_fd(tab, '%', STDOUT);
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), STDOUT);
	*nb_char += nb;
}

void	str_decimal(va_list ap, int *nb_char, int *tab)
{
	unsigned int	u;
	int				len;
	int				nb;

	nb = 0;
	u = va_arg(ap, unsigned int);
	len = ft_nbrlen_base(u, 10);
	nb += ft_put_zero_and_space(u, tab, len, STDOUT);
	nb += ft_putnbrn_fd(u, tab, STDOUT);
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), STDOUT);
	*nb_char += nb;
}
