/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:08:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/23 09:35:35 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*ft_get_var_env(t_shell *shell, char *name)
{
	t_env	*begin;
	int		len;

	len = ft_strlen(name);
	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, len))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}

int		get_var_env(t_shell *shell, char *var_name, char **content, int unset)
{
	t_env	*begin;

	*content = NULL;
	if (var_name && ft_isdigit(var_name[0]) && !var_name[1])
	{
		if (!(*content = malloc_lst(shell, 1)))
			ft_exit_failure(shell, F_MALLOC, NULL);
		(*content)[0] = 0;
		return (1);
	}
	if (var_name && var_name[0] == '?' && !var_name[1])
	{
		if (!(*content = ft_itoa(shell->exit)) ||
			!add_lst_to_free(shell, content))
			ft_exit_failure(shell, F_MALLOC, content);
		return (1);
	}
	begin = shell->var_env;
	return (ft_prepare_env(unset, begin, var_name, content));
}

void	ft_sort_export_var(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr && ptr->next)
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
		{
			ft_swap_env_all(ptr, ptr->next);
			ptr = env;
		}
		else
			ptr = ptr->next;
}

t_env	*ft_clone_export_env(t_shell *shell, t_env *lst)
{
	t_env	*sorted;

	if (lst == NULL)
		return (NULL);
	if (!(sorted = malloc_lst(shell, sizeof(t_env))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(sorted->content = ft_strdup(lst->content)) ||
		!add_lst_to_free(shell, sorted->content))
		ft_exit_failure(shell, F_MALLOC, sorted->content);
	if (!(sorted->name = ft_strdup(lst->name)) ||
		!add_lst_to_free(shell, sorted->name))
		ft_exit_failure(shell, F_MALLOC, sorted->name);
	sorted->hidden = lst->hidden;
	sorted->next = ft_clone_export_env(shell, lst->next);
	return (sorted);
}
