/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 15:57:46 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_add_new_env(t_shell *shell, t_tree *node)
{
	int		i;
	int		j;
	t_env	*new_lst;

	i = -1;
	j = -1;
	new_lst = malloc_lst(shell, sizeof(t_env));
	return (SUCCESS);
}

int		ft_export(t_shell *shell, t_tree *node)
{
	if (node->left->item)
		ft_add_new_env(shell, node);
	(void)node;
	
	return (SUCCESS);
}