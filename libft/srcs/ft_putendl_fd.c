/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:24:24 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 11:25:14 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		s_len;
	char	c;

	c = '\n';
	if (!s)
		return ;
	s_len = ft_strlen(s);
	write(fd, s, s_len);
	write(fd, &c, 1);
}
