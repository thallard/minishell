/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:36:19 by thallard          #+#    #+#             */
/*   Updated: 2021/01/23 09:12:32 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_prepare_tab_change_value(t_shell *shell, char *name, int *i)
{
	char	*var;

	*i = -1;
	if (!(var = ft_strdup(name)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
	if (!(var = ft_strjoin(var, "=")) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
	return (var);
}

int		ft_prepare_env(int unset, t_env *begin, char *var_name, char **content)
{
	while (begin)
	{
		if (!ft_strncmp(begin->name, var_name, ft_strlen(var_name) + 1))
		{
			if (unset == 0 || begin->hidden != UNSET)
				*content = begin->content;
			if (!(*content))
				return (0);
			return (1);
		}
		begin = begin->next;
	}
	return (-1);
}
