/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:30:36 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:46:49 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putcharn_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstrn_fd(char *s, int n, int fd)
{
	int s_len;

	if (!s)
	{
		write(fd, "(null)", n);
		return (n);
	}
	s_len = ft_min_printf(ft_strlen_printf(s), n);
	write(fd, s, s_len);
	return (s_len);
}

int	ft_putnbrn_fd(long long int n, int *tab, int fd)
{
	if (n == 0 && tab[2] == 0)
	{
		if (tab[0] || tab[4])
			return (ft_putcharn_fd(' ', fd));
		return (0);
	}
	if (n < 0)
	{
		ft_putcharn_fd('-', fd);
		return (1 + ft_putnbrn_fd(-n, tab, fd));
	}
	if (n < 10)
		return (ft_putcharn_fd(n + '0', fd));
	else
	{
		tab[2] = 1;
		return (ft_putnbrn_fd(n / 10, tab, fd) +
				ft_putnbrn_fd(n % 10, tab, fd));
	}
}

int	print_base_fd(unsigned long add, int *tab, int fd, char *base)
{
	unsigned long	l_base;
	int				nb;

	l_base = ft_strlen_printf(base);
	nb = 0;
	if (add == 0 && tab[2] == 0)
	{
		if (tab[0] || tab[4])
			return (ft_putcharn_fd(' ', fd));
		return (0);
	}
	if (add < l_base)
		return (ft_putcharn_fd(base[add], fd));
	tab[2] = 1;
	nb += print_base_fd(add / l_base, tab, fd, base);
	nb += print_base_fd(add % l_base, tab, fd, base);
	return (nb);
}

int	ft_put_sign_fd(int fd)
{
	return (ft_putcharn_fd('-', fd));
}
