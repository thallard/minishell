/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:48:28 by thallard          #+#    #+#             */
/*   Updated: 2021/01/21 15:16:25 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		ft_unset_hide_env(t_env **env, char *name)
{
	t_env	*begin;

	begin = *env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, ft_strlen(name) + 1))
		{
			// begin->content = "";
			begin->content = ft_strdup("");	// a proteger
			begin->hidden = UNSET;
			return (SUCCESS);
		}
		begin = begin->next;
	}
	return (FAILURE);
}
