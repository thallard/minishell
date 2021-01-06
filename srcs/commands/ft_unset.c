/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:42:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 10:46:16 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_search_wrong_character(char *str)
{
	int		i;
	int		alpha;

	alpha = 0;
	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
			alpha = 1;
		else if ((str[i] == '-') ||
				(alpha == 0 && ft_isdigit(str[i])))
			return (0);
	return (1);
}

int		ft_unset(t_shell *shell, t_tree *node)
{
	char	**tab;
	int		row;

	if (!node->left->item)
	{
		shell->exit = 1;
		return (FAILURE);
	}
	else
	{
		row = -1;
		tab = ft_split_minishell(node->left->item, ' ', shell);
		while (tab[++row])
			if ((ft_search_wrong_character(tab[row])) == 1)
				ft_env_remove_if(&shell->var_env, node->left->item, &ft_strncmp);
			else
				print_unset_error(shell, tab[row]);
	}
	shell->exit = 0;
	return (SUCCESS);
}