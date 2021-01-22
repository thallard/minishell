/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill_lst_and_swap.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:22:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 16:44:57 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		ft_swap_env_all(t_env *a, t_env *b)
{
	char	*temp;
	int		hidden;

	temp = a->name;
	a->name = b->name;
	b->name = temp;
	temp = a->content;
	a->content = b->content;
	b->content = temp;
	hidden = a->hidden;
	a->hidden = b->hidden;
	b->hidden = hidden;
}

void		ft_swap_env_content(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

char		*ft_fill_env_content(t_shell *shell, char *str)
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
	int		i;

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
	t_env	*new_lst;

	ft_fill_tab_env(shell, envp);
	shell->var_env = NULL;
	i = -1;
	while (shell->tab_env[++i])
	{
		ft_bzero(str, 10000);
		ft_finish_fill_env(shell, str, &new_lst, shell->tab_env[i]);
	}
	if (!ft_get_var_env(shell, "OLDPWD"))
		replace_env_content(shell, "OLDPWD", "", NOT_PRINT);
	ft_set_shlvl(shell);
	return (SUCCESS);
}
