/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/03 15:08:55 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		main()
{
	int		res;
	char	*path;

	path = calloc(1, 500);
	getcwd(path, 500);
	ft_printf("%s\n", path);
	return (res);
}