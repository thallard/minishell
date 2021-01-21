/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:48:28 by thallard          #+#    #+#             */
/*   Updated: 2021/01/21 14:35:06 by thallard         ###   ########lyon.fr   */
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
			begin->content = "";
			begin->hidden = UNSET;
			return (SUCCESS);
		}
		begin = begin->next;
	}
	return (FAILURE);
}
