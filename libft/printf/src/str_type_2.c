/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_type_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:57:24 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 10:34:57 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	str_add_hexa(int fd, va_list ap, int *nb_char, int *tab)
{
	void			*p;
	unsigned long	add;
	int				len;
	int				nb;

	nb = 0;
	p = va_arg(ap, void*);
	add = (unsigned long)(p);
	len = ft_nbrlen_base_add(add, 16);
	if (tab[0] < 0)
	{
		tab[0] *= -1;
		nb += ft_putspace(1, fd);
	}
	nb += ft_put_zero_and_space_add(tab, len, fd);
	nb += print_base_fd(add, tab, fd, "0123456789abcdef");
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), fd);
	*nb_char += nb;
}

void	str_unsigned_hexa_x(int fd, va_list ap, int *nb_char, int *tab)
{
	unsigned int	x;
	int				len;
	int				nb;

	nb = 0;
	x = va_arg(ap, unsigned int);
	len = ft_nbrlen_base(x, 16);
	nb += ft_put_zero_and_space(x, tab, len, fd);
	nb += print_base_fd(x, tab, fd, "0123456789abcdef");
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), fd);
	*nb_char += nb;
}

void	str_unsigned_hexa_x_maj(int fd, va_list ap, int *nb_char, int *tab)
{
	unsigned int	x;
	int				len;
	int				nb;

	nb = 0;
	x = va_arg(ap, unsigned int);
	len = ft_nbrlen_base(x, 16);
	nb += ft_put_zero_and_space(x, tab, len, fd);
	nb += print_base_fd(x, tab, fd, "0123456789ABCDEF");
	nb += ft_putspace(ft_max_printf(tab[1] - nb, 0), fd);
	*nb_char += nb;
}

int		ft_putchar_and_space_fd(int *tab, char c, int fd)
{
	int	nb_space;
	int	nb_zero;
	int nb;

	nb_zero = ft_max_printf(tab[0] - 1, 0);
	nb_space = ft_max_printf(tab[4] - 1, 0);
	nb = 0;
	nb += ft_putzero(nb_zero, fd);
	nb += ft_putspace(nb_space, fd);
	nb += ft_putcharn_fd(c, fd);
	return (nb);
}

int		ft_putstr_and_space_fd(int *tab, char *s, int fd)
{
	int	len;
	int	nb_space;
	int	nb_c;

	if (!s)
		len = 6;
	else
		len = ft_strlen_printf(s);
	if (tab[2] < 0)
		tab[2] = len;
	nb_c = ft_min_printf(len, tab[2]);
	nb_space = ft_max_printf(ft_max_printf(tab[0], tab[4]) - nb_c, 0);
	return (ft_putspace(nb_space, fd) + ft_putstrn_fd(s, nb_c, fd));
}
