/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:36:26 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 17:34:25 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_fd	*ft_lstfdnew(t_shell *shell, int fd)
{
	t_fd	*elem;

	if (!(elem = malloc(sizeof(t_fd))) || !add_lst_to_free(shell, elem))
		ft_exit_failure(shell, F_MALLOC, elem);
	elem->fd = fd;
	elem->next = NULL;
	return (elem);
}

static t_fd	*ft_lstfdlast(t_fd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static t_fd	*ft_lstfdadd_back(t_shell *shell, int fd)
{
	t_fd	*elem;
	t_fd	*new;

	if (!(new = ft_lstfdnew(shell, fd)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!shell->lst_fd)
		shell->lst_fd = new;
	else
	{
		elem = ft_lstfdlast(shell->lst_fd);
		elem->next = new;
	}
	return (shell->lst_fd);
}

static int	ft_dir_error(t_shell *shell)
{
	int fd;

	if (shell->dir_err)
	{
		if ((fd = open(shell->dir_err,
			O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1)
			return (print_error(shell, "fd", 1));
		if (dup2(fd, STDERR_FILENO) == -1)
			return (print_error(shell, "dup", 1));
	}
	return (SUCCESS);
}

int			manage_redirection(t_shell *shell, t_dir *exec_dir)
{
	int	i;
	int	fd;

	i = -1;
	while (exec_dir[++i].file)
	{
		if (exec_dir[i].dir >= 0)
		{
			if ((exec_dir[i].dir == 1 && (fd = open(exec_dir[i].file,
				O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1) ||
				(exec_dir[i].dir == 2 && (fd = open(exec_dir[i].file,
				O_APPEND | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1))
				return (print_error(shell, "fd", 1));
			if (!(ft_lstfdadd_back(shell, fd)) || dup2(fd, 1) == -1)
				return (print_error(shell, "dup", 1));
		}
		if (exec_dir[i].dir == -1)
		{
			if ((fd = open(exec_dir[i].file, O_RDONLY, 0666)) == -1)
				return (print_error(shell, exec_dir[i].file, 1));
			if (dup2(fd, STDIN_FILENO) == -1)
				return (print_error(shell, "dup", 1));
		}
	}
	return (ft_dir_error(shell));
}
