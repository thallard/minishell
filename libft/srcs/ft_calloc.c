/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:36:04 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 12:41:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (!nmemb || !size)
	{
		if (!(res = malloc(1)))
			return (NULL);
		return (res);
	}
	if (!(res = malloc(nmemb * size)))
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}
