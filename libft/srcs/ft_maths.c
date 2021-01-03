/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 07:51:33 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:51:33 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int x, int y)
{
	if (x >= y)
		return (x);
	return (y);
}

int	ft_min(int x, int y)
{
	if (x <= y)
		return (x);
	return (y);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}