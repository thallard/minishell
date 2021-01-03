/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:20:47 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 13:03:56 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	i;
	size_t	j;

	ptr1 = (char*)str;
	ptr2 = (char*)to_find;
	i = 0;
	if (!ptr2[0])
		return (ptr1);
	while (i < n && ptr1[i])
	{
		j = 0;
		while (ptr1[i + j] == ptr2[j] && ptr2[j] && i + j < n)
			j++;
		if (!ptr2[j])
			return (ptr1 + i);
		i++;
	}
	return (NULL);
}
