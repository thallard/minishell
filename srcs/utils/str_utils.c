/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:26:10 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 15:26:10 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int	ft_strrfind(const char *s, int c)
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
