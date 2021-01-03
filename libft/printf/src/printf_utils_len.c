/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:47:19 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:37:32 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_zero_printf(void *s, size_t n)
{
	size_t	i;
	int		*ptr;

	ptr = (int*)s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
	ptr[2] = -1;
}

int		ft_strlen_printf(const char *str)
{
	int nb;

	nb = 0;
	while (str[nb])
	{
		nb = nb + 1;
	}
	return (nb);
}

int		ft_nbrlen_base(long long i, long long l_base)
{
	if (i < 0)
		return (1 + ft_nbrlen_base(-i, l_base));
	if (i < l_base)
		return (1);
	return (1 + ft_nbrlen_base(i / l_base, l_base));
}

int		ft_nbrlen_base_add(unsigned long i, unsigned long l_base)
{
	if (i < l_base)
		return (1);
	return (1 + ft_nbrlen_base(i / l_base, l_base));
}

void	ft_add_digit_to_tab(va_list ap, char **str, int *tab)
{
	if (**str == '0')
		tab[0] = ft_atoi_simplify(ap, str);
	else
		tab[4] = ft_atoi_simplify(ap, str);
}
