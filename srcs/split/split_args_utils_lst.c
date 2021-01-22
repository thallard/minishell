/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:35:15 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 14:54:46 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var_s	*ft_lstvarnew(t_shell *shell, int len)
{
	t_var_s	*elem;

	if (!(elem = malloc_lst(shell, sizeof(t_var_s))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	elem->len = len;
	elem->next = NULL;
	return (elem);
}

static t_var_s	*ft_lstvarlast(t_var_s *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_var_s			*ft_lstvaradd_back(t_shell *shell, t_args *args,
				int len, int ind)
{
	t_var_s	*elem;
	t_var_s	*new;

	if (!(new = ft_lstvarnew(shell, len)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!args->var[ind])
		args->var[ind] = new;
	else
	{
		elem = ft_lstvarlast(args->var[ind]);
		elem->next = new;
	}
	return (args->var[ind]);
}

t_var_s			*ft_lstvaradd_back_dir(t_shell *shell, t_dir *dir,
				int len, int ind)
{
	t_var_s	*elem;
	t_var_s	*new;

	if (!(new = ft_lstvarnew(shell, len)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!dir[ind].var)
		dir[ind].var = new;
	else
	{
		elem = ft_lstvarlast(dir[ind].var);
		elem->next = new;
	}
	return (dir[ind].var);
}
