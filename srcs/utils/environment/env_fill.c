/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:22:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/21 14:31:16 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_swap_env_all(t_env *a, t_env *b)
{
	char *lastName;
	int		hidden;

	lastName = a->name;
	a->name = b->name;
	b->name = lastName;

	lastName = a->content;
	a->content = b->content;
	b->content = lastName;

	hidden = a->hidden;
	a->hidden = b->hidden;
	b->hidden = hidden;
}

void	ft_swap_env_content(t_env *a, t_env *b)
{
	char *lastName;

	lastName = a->content;
	a->content = b->content;
	b->content = lastName;
}

static char	*ft_fill_env_content(t_shell *shell, char *str)
{
	char	*content;
	int		i;

	if (!(content = malloc(sizeof(char) * (ft_strlen(str) + 1))) ||
		!(add_lst_to_free(shell, content)))
		ft_exit_failure(shell, F_MALLOC, content);
	i = -1;
	while (str[++i])
		content[i] = str[i];
	content[i] = '\0';
	return (content);
}

static int	ft_fill_tab_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (!(shell->tab_env = malloc_lst(shell, sizeof(char *) * (i + 2))))
		ft_exit_failure(shell, F_MALLOC, shell->tab_env);
	i = -1;
	while (envp[++i])
	{
		if (!(shell->tab_env[i] = malloc_lst(shell, ft_strlen(envp[i]) + 100)))
			ft_exit_failure(shell, F_MALLOC, NULL);
		shell->tab_env[i] = envp[i];
	}
	shell->tab_env[i] = NULL;

	


	
	return (SUCCESS);
}

int			ft_fill_lst_env(t_shell *shell, char **envp)
{
	char	str[10000];
	int		i;
	int		j;
	t_env	*new_lst;

	ft_fill_tab_env(shell, envp);
	shell->var_env = NULL;
	i = -1;
	while (shell->tab_env[++i])
	{
		ft_bzero(str, ft_strlen(str));
		j = -1;
		if (!(new_lst = malloc_lst(shell, sizeof(t_env))))
			ft_exit_failure(shell, F_MALLOC, NULL);
		new_lst->next = NULL;
		while (shell->tab_env[i][++j] && shell->tab_env[i][j] != '=')
			str[j] = shell->tab_env[i][j];
		if (shell->tab_env[i][j] == '=')
			new_lst->hidden = TO_PRINT;
		else
			new_lst->hidden = NOT_PRINT;
		str[j] = '\0';
		if (!(new_lst->name = ft_strdup(str)) ||
			!(add_lst_to_free(shell, new_lst->name)))
			ft_exit_failure(shell, F_MALLOC, new_lst->name);
		new_lst->content = ft_fill_env_content(shell, &shell->tab_env[i][j + 1]);
		ft_env_add_back(&shell->var_env, new_lst);
	}	
	if (!ft_get_var_env(shell, "OLDPWD"))
		replace_env_content(shell, "OLDPWD", "", NOT_PRINT);	// 1 ? 0 ? 3 ?
	return (SUCCESS);
}
