/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:42:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 10:02:34 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_search_wrong_character(t_tree *node, char **tab)
{
	int		i;
	int		alpha;

	(void)tab;
	alpha = 0;
	i = -1;
	while (((char *)node->left->item)[++i])
		if (ft_isalpha(((char *)node->left->item)[i]))
			alpha = 1;
		else if ((((char *)node->left->item)[i] == '-') ||
				(alpha == 0 && ft_isdigit(((char *)node->left->item)[i])))
			return (0);
		
	return (1);
}

int		ft_unset(t_shell *shell, t_tree *node)
{
	char	**tab;

	if (!node->left->item)
	{
		shell->exit = 1;
		return (FAILURE);
	}
	else
	{
		tab = ft_split_minishell(node->left->item, ' ', shell);
		if ((ft_search_wrong_character(node, tab)) == 1)
			ft_env_remove_if(&shell->var_env, node->left->item, &ft_strncmp);
		else
			return (print_unset_error(shell, node->left->item));		
	}
	shell->exit = 0;
	return (SUCCESS);
}