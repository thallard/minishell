/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/07 10:33:04 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell)
{
	int		res;
	char	*path;

	(void)shell;
	res = 0;
	path = ft_calloc(1, 500);
	getcwd(path, 500);
	ft_printf(1, "%s\n", path);
	return (res);
}