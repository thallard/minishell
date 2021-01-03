/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:17:17 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/25 16:09:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		s_len;
	int		i;
	int		j;
	char	*res;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1);
	i = 0;
	while (s1[i] && is_inset(s1[i], set))
		i++;
	s_len = s_len - 1;
	while (s_len > i && is_inset(s1[s_len], set))
		s_len--;
	if (!(res = malloc(sizeof(char) * (s_len - i + 2))))
		return (NULL);
	j = 0;
	while (i <= s_len)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}
