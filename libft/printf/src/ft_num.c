/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:28:09 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:46:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_max_printf(int x, int y)
{
	if (x >= y)
		return (x);
	return (y);
}

int	ft_min_printf(int x, int y)
{
	if (x <= y)
		return (x);
	return (y);
}

int	ft_abs_printf(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_is_digit_printf(int i)
{
	return (i >= '0' && i <= '9');
}
