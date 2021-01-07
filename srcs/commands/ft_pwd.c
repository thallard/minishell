/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/07 14:38:37 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell, int pipe_fd[2], int is_pipe)
{
	int		res;
	char	*path;
	int		fd;

	fd = 1;
	(void)shell;
	res = 0;
	path = ft_calloc(1, 500);
	getcwd(path, 500);
	if (is_pipe == PIPE_OUT) // quid de PIPE_IN ??
		fd = pipe_fd[1];
	ft_printf(fd, "%s\n", path);
	return (res);
}