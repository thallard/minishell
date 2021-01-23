/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 09:07:43 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 09:07:46 by bjacob           ###   ########lyon.fr   */
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
