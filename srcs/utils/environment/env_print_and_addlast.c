/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_and_addlast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:23:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 15:31:29 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env		*ft_env_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void		ft_env_add_back(t_env **alst, t_env *new)
{
	t_env	*elem;

	if (!(*alst))
		*alst = new;
	else
	{
		elem = ft_env_last(*alst);
		elem->next = new;
	}
}

t_args		*ft_finish_fill_env(t_shell *shell, char *str,
			t_env **new_lst, char *arg)
{
	int		j;

	j = -1;
	if (!(*new_lst = malloc_lst(shell, sizeof(t_env))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	(*new_lst)->next = NULL;
	while (arg[++j] && arg[j] != '=')
		str[j] = arg[j];
	if (arg[j] == '=')
		(*new_lst)->hidden = TO_PRINT;
	else
		(*new_lst)->hidden = NOT_PRINT;
	str[j] = '\0';
	if (!((*new_lst)->name = ft_strdup(str)) ||
		!(add_lst_to_free(shell, (*new_lst)->name)))
		ft_exit_failure(shell, F_MALLOC, (*new_lst)->name);
	(*new_lst)->content = ft_fill_env_content(shell, &arg[j + 1]);
	ft_env_add_back(&shell->var_env, *new_lst);
	return (NULL);
}

void		ft_print_env_var(t_env *var_end)
{
	while (var_end)
	{
		if (var_end->hidden == TO_PRINT)
			ft_printf(1, "%s=%s\n", var_end->name, var_end->content);
		var_end = var_end->next;
	}
}

void		ft_print_export_var(t_env *var_end)
{
	while (var_end)
	{
		if (!ft_strncmp(var_end->name, "_", 2))
			var_end = var_end->next;
		if (var_end->hidden == NOT_PRINT)
			ft_printf(1, "declare -x %s\n", var_end->name, var_end->hidden);
		else if (var_end->hidden == TO_PRINT)
			ft_printf(1, "declare -x %s=\"%s\"\n", var_end->name,
			var_end->content, var_end->hidden);
		var_end = var_end->next;
	}
}
