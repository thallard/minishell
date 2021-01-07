/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:49:55 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 10:34:47 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	fill_tab_indic(va_list ap, char **str, int *tab)
{
	int	etoile;

	if (ft_is_digit_printf(**str) && !tab[1])
		ft_add_digit_to_tab(ap, str, tab);
	if (**str == '-')
	{
		tab[1] = ft_abs_printf(ft_atoi_simplify(ap, str));
		tab[0] = 0;
	}
	if (**str == '.')
		tab[2] = ft_atoi_simplify(ap, str);
	if (**str == '*')
	{
		etoile = ft_atoi_simplify(ap, str);
		if (etoile < 0)
			tab[1] = -etoile;
		else
			tab[4] = etoile;
	}
	if (tab[0] < 0)
	{
		tab[1] = tab[0] * (-1);
		tab[0] = 0;
	}
}

void	str_convert(int fd, va_list ap, char **str, int *nb_char)
{
	int	tab[5];

	(void)fd;
	ft_zero_printf(tab, 5);
	while (ft_is_digit_printf(**str) || **str == '-'
			|| **str == '.' || **str == '*')
		fill_tab_indic(ap, str, tab);
	if (**str == 'c')
		str_char(fd, ap, nb_char, tab);
	if (**str == 's')
		str_string(fd, ap, nb_char, tab);
	if (**str == 'p')
		str_add_hexa(fd, ap, nb_char, tab);
	if (**str == 'i' || **str == 'd')
		str_int(fd, ap, nb_char, tab);
	if (**str == 'u')
		str_decimal(fd, ap, nb_char, tab);
	if (**str == 'x')
		str_unsigned_hexa_x(fd, ap, nb_char, tab);
	if (**str == 'X')
		str_unsigned_hexa_x_maj(fd, ap, nb_char, tab);
	if (**str == '%')
		str_percent(fd, nb_char, tab);
}

void	str_process(int fd, va_list ap, char **str, int *nb_char)
{
	if (*(*str) == '%')
	{
		(*str)++;
		str_convert(fd, ap, str, nb_char);
	}
	else
		*nb_char += ft_putcharn_fd(**str, fd);
	(*str)++;
}

int		ft_printf(int fd, const char *format, ...)
{
	va_list	ap;
	char	*str;
	int		nb_char;

	str = (char*)format;
	va_start(ap, format);
	nb_char = 0;
	while (*str)
		str_process(fd, ap, &str, &nb_char);
	va_end(ap);
	return (nb_char);
}
