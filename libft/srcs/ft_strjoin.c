/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:22:19 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 11:22:26 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	while (++i < l1)
		str[i] = s1[i];
	while (++j < l2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}
