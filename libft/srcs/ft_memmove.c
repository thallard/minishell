/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:24:52 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 11:24:58 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char*)dest;
	ptr2 = (char*)src;
	if (!dest && !src)
		return (NULL);
	if (ptr1 < ptr2)
	{
		i = -1;
		while (++i < n)
			ptr1[i] = ptr2[i];
	}
	else
	{
		i = n;
		while (i > 0)
		{
			ptr1[i - 1] = ptr2[i - 1];
			i--;
		}
	}
	return (dest);
}
