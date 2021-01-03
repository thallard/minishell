/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:49:55 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:47:35 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	str_convert(va_list ap, char **str, int *nb_char)
{
	int	tab[5];

	ft_zero_printf(tab, 5);
	while (ft_is_digit_printf(**str) || **str == '-'
			|| **str == '.' || **str == '*')
		fill_tab_indic(ap, str, tab);
	if (**str == 'c')
		str_char(ap, nb_char, tab);
	if (**str == 's')
		str_string(ap, nb_char, tab);
	if (**str == 'p')
		str_add_hexa(ap, nb_char, tab);
	if (**str == 'i' || **str == 'd')
		str_int(ap, nb_char, tab);
	if (**str == 'u')
		str_decimal(ap, nb_char, tab);
	if (**str == 'x' || **str == 'X')
		str_unsigned_hexa(ap, str, nb_char, tab);
	if (**str == '%')
		str_percent(nb_char, tab);
}

void	str_process(va_list ap, char **str, int *nb_char)
{
	if (*(*str) == '%')
	{
		(*str)++;
		str_convert(ap, str, nb_char);
	}
	else
		*nb_char += ft_putcharn_fd(**str, STDOUT);
	(*str)++;
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*str;
	int		nb_char;

	str = (char*)format;
	va_start(ap, format);
	nb_char = 0;
	while (*str)
		str_process(ap, &str, &nb_char);
	va_end(ap);
	return (nb_char);
}
