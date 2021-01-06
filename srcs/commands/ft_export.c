/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 15:48:28 by thallard         ###   ########lyon.fr   */
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
	if (!(new_lst->name = malloc(sizeof(char) * (ft_strlen(tab[i]) + 1))) ||
		!(add_lst_to_free(shell, new_lst->name)))
		return (NULL);
	if (!(new_lst->content = malloc(sizeof(char) * (ft_strlen(tab[i]) + 1))) ||
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
			if (env->hidden == 2 || ((char *)shell->var_env->content)[0] == '\0')
			{
					env->hidden = 0;
				shell->var_env->hidden = 0;
					free(shell->var_env->content);
				shell->var_env->content = content;

				shell->var_env = begin;

				
				
			return (SUCCESS);
			}
		}
	}
	shell->var_env->next = env;
	shell->var_env = begin;
	return (FAILURE);
}

int		ft_filter_and_add(t_shell *shell, t_env *env, char *str, int j)
{
	int		k;

	k = 0;
	if (j <= ft_strlen(str) && ((char *)env->content)[0] != '\0' && env->hidden != 2)
		{
			if (str[j] == ' ')
				j = ft_strlen(str) + 1;
			while (str[j])
				((char *)env->content)[k++] = str[j++];
			((char *)env->content)[k] = '\0';
			// dprintf(1, "debug du k pour le 0 %d et du content %s\n", k, env->content);
			env->hidden = 0;
			ft_if_env_exists(shell, env->name, env->content, env);
		}
		else if (env->hidden != 2)
		{
			env->hidden = 1;
			((char *)env->content)[k] = '\0';
			ft_if_env_exists(shell, env->name, env->content, env);
		}
		else if (env->hidden == 2)
		{
			((char *)env->content)[k] = '\0';
			ft_if_env_exists(shell, env->name, env->content, env);
		}
	return (SUCCESS);
}

int		ft_add_new_env(t_shell *shell, t_tree *node)
{
	int		i;
	int		j;
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
		if (tab[i][j] == '=' && !tab[i][j + 1])
			new_lst->hidden = 2;
		else
			new_lst->hidden = 0;
		new_lst->name[j++] = '\0';
		//  dprintf(1, "debug str = %s\n", tab[i]);
		if ((j + 3) <= ft_strlen(tab[i]))
			if (ft_strncmp(&tab[i][j], "\"\"", 3) == 0)
				((char *)new_lst->content)[0] = '\0';
		ft_filter_and_add(shell, new_lst, tab[i], j);
			
		// ft_print_env_var(shell->var_env);
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