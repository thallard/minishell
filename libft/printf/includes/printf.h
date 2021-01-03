/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:52:12 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/22 07:46:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

void	str_convert(va_list ap, char **str, int *nb_char);
void	str_process(va_list ap, char **str, int *nb_char);
int		ft_printf(const char *format, ...) __attribute__((format(printf,1,2)));

void	str_int(va_list ap, int *nb_char, int *tab);
void	str_char(va_list ap, int *nb_char, int *tab);
void	str_string(va_list ap, int *nb_char, int *tab);
void	str_percent(int *nb_char, int *tab);
void	str_decimal(va_list ap, int *nb_char, int *tab);

void	fill_tab_indic(va_list ap, char **str, int *tab);
void	str_add_hexa(va_list ap, int *nb_char, int *tab);
void	str_unsigned_hexa(va_list ap, char **str, int *nb_char, int *tab);
int		ft_putchar_and_space_fd(int *tab, char c, int fd);
int		ft_putstr_and_space_fd(int *tab, char *s, int fd);

int		ft_putcharn_fd(char c, int fd);
int		ft_putstrn_fd(char *s, int n, int fd);
int		ft_putnbrn_fd(long long int n, int *tab, int fd);
int		print_base_fd(unsigned long add, int *tab, int fd, char *base);
int		ft_put_sign_fd(int fd);

int		ft_atoi_simplify(va_list ap, char **str);
int		ft_putspace(int nb, int fd);
int		ft_putzero(int nb, int fd);
int		ft_put_zero_and_space(long long i, int *tab, int l_i, int fd);
int		ft_put_zero_and_space_add(int *tab, int len, int fd);

void	ft_zero_printf(void *s, size_t n);
int		ft_strlen_printf(const char *str);
int		ft_nbrlen_base(long long i, long long l_base);
int		ft_nbrlen_base_add(unsigned long i, unsigned long l_base);
void	ft_add_digit_to_tab(va_list ap, char **str, int *tab);

int		ft_max_printf(int x, int y);
int		ft_min_printf(int x, int y);
int		ft_abs_printf(int x);
int		ft_is_digit_printf(int i);

# ifndef STDOUT
#  define STDOUT 1
# endif

#endif
