/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:36:26 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 13:33:52 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_fd	*ft_lstfdnew(int fd)
{
	t_fd	*elem;

	if (!(elem = malloc(sizeof(t_fd))))
		return (NULL);
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

static t_fd	*ft_lstfdadd_back(t_fd **alst, int fd)
{
	t_fd	*elem;
	t_fd	*new;

	if (!(new = ft_lstfdnew(fd)))
		return (NULL);
	if (!(*alst))
		*alst = new;
	else
	{
		elem = ft_lstfdlast(*alst);
		elem->next = new;
	}
	return (*alst);
}

void		ft_lstfd_close_clear(t_fd **lst)
{
	t_fd	*elem;
	t_fd	*next;

	elem = *lst;
	while (elem)
	{
		next = elem->next;
		close(elem->fd);
		free(elem);
		elem = next;
	}
	*lst = NULL;
}

int			manage_redirection(t_shell *shell, t_dir **exec_dir)
{
	int 	i;
	int		fd;

	i = -1;
	while (exec_dir[++i]->file)
	{
// dprintf(shell->std[1], "file = %s, dir = %d\n", exec_dir[i]->file, exec_dir[i]->dir);		
		
		if (exec_dir[i]->dir >= 0)
		{
			if ((exec_dir[i]->dir == 1 && (fd = open(exec_dir[i]->file,
				O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1) ||
				(exec_dir[i]->dir == 2 && (fd = open(exec_dir[i]->file,
				O_APPEND | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1))
				return (FAILURE);
			if (!(ft_lstfdadd_back(&(shell->lst_fd), fd)) || dup2(fd, 1) == -1)
				return (FAILURE);
		}
		if (exec_dir[i]->dir == -1)
		{
			if ((fd = open(exec_dir[i]->file, O_RDONLY, 0666)) == -1)
				return (FAILURE);	// a gerer avec errno
			dup2(fd, STDIN_FILENO);
		}
	}
	return (SUCCESS);
}
