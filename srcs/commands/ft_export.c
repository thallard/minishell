/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 09:57:17 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

t_env	*ft_prepare_lst_env(t_shell *shell, t_tree *node, char **tab, int i)
{
	t_env	*new_lst;

	(void)node;
	new_lst = NULL;
	if (!(new_lst = malloc_lst(shell, sizeof(t_env))) ||
		!(add_lst_to_free(shell, new_lst)))
		return (NULL);
	new_lst->next = NULL;
	if (!(new_lst->name = malloc(sizeof(char) * ft_strlen(tab[i]))) ||
		!(add_lst_to_free(shell, new_lst->name)))
		return (NULL);
	if (!(new_lst->content = malloc(sizeof(char) * ft_strlen(tab[i]))) ||
		!(add_lst_to_free(shell, new_lst->content)))
		return (NULL);
	return (new_lst);
}

int		ft_if_env_exists(t_shell *shell, char *name, char *content, t_env *env)
{
	t_env	*begin;

	begin = shell->var_env;
	while (shell->var_env->next)
	{
		shell->var_env = shell->var_env->next;
		if (ft_strncmp(shell->var_env->name, name, (ft_strlen(name) + 1)) == 0)
		{
			dprintf(1, "difference %s et %s\n", shell->var_env->name, name);
			free(shell->var_env->content);
			shell->var_env->content = content;
			shell->var_env = begin;
			return (SUCCESS);
		}
	}
	shell->var_env->next = env;
	shell->var_env = begin;
	return (FAILURE);
}

int		ft_add_new_env(t_shell *shell, t_tree *node)
{
	int		i;
	int		j;
	int		k;
	t_env	*new_lst;
	char	**tab;

	tab = ft_split_minishell(node->left->item, ' ', shell);
	i = -1;
	while (tab[++i])
	{
		new_lst = ft_prepare_lst_env(shell, node, tab, i);
		j = -1;
		while (tab[i][++j] && tab[i][j] != '=')
			new_lst->name[j] = tab[i][j];
		new_lst->name[j++] = '\0';
		k = -1;
		while (tab[i][j])
			((char *)new_lst->content)[++k] = tab[i][j++];
		((char *)new_lst->content)[++k] = '\0';
		ft_if_env_exists(shell, new_lst->name, new_lst->content, new_lst);
			ft_print_env_var(shell->var_env);
	}
	return (SUCCESS);
}

int		ft_export(t_shell *shell, t_tree *node)
{
	if (node->left->item)
	{
		if (ft_add_new_env(shell, node))
		{
			shell->exit = 0;
			return (SUCCESS);
		}
		else
		{
			shell->exit = 1;
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}