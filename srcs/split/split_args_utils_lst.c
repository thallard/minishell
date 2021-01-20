/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:35:15 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/20 09:31:22 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var_status	*ft_lstvarnew(int len)
{
	t_var_status	*elem;

	if (!(elem = malloc(sizeof(t_var_status))))
		return (NULL);	// a securiser
	elem->len = len;
	elem->next = NULL;
	return (elem);
}

static t_var_status	*ft_lstvarlast(t_var_status *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_var_status	*ft_lstvaradd_back(t_shell *shell, t_args *args,
				int len, int ind)
{
	t_var_status	*elem;
	t_var_status	*new;

	if (!(new = ft_lstvarnew(len)))
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

t_var_status	*ft_lstvaradd_back_dir(t_shell *shell, t_dir *dir,
				int len, int ind)
{
	t_var_status	*elem;
	t_var_status	*new;

	if (!(new = ft_lstvarnew(len)))
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
