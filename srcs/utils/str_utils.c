/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:46:32 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 12:00:15 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_strrfind(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char*)s;
	if (!ptr)
		return (-1);
	i = 0;
	while (ptr[i])
		i++;
	while (i >= 0 && ptr[i] != (char)c)
		i--;
	return (i);
}

char	*ft_remove_eol(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
	return (str);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
