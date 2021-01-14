/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:22:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/14 11:54:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_swap_env_all(t_env *a, t_env *b)
{
	char *lastName;

	lastName = a->name;
	a->name = b->name;
	b->name = lastName;

	lastName = a->content;
	a->content = b->content;
	b->content = lastName;
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

	if (!(content = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	if (!(add_lst_to_free(shell, content)))
		return (NULL);
	i = -1;
	while (str[++i])
		content[i] = str[i];
	content[i] = '\0';
	return (content);
}

static int	ft_fill_tab_env(t_shell *shell, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		;
	if (!(shell->tab_env = malloc(100000)))
		return (FAILURE);
	i = -1;
	while (envp[++i])
	{
		shell->tab_env[i] = malloc_lst(shell, sizeof(char) * ft_strlen(envp[i]) + 100);
		shell->tab_env[i] = envp[i];
	}
	shell->tab_env[i] = NULL;
// 	if (stat("env_file", &fd_status) == -1)
// 		return (FAILURE);

// // ft_printf(1, "p0\n");	//////////////////


// 	fd = open("env_file", O_RDONLY);
// 	read(fd, str_file, 10000);
// 	if (!(shell->tab_env = ft_split_minishell(str_file, '\n', shell)))
// 		return (FAILURE);
	return (SUCCESS);
}

int			ft_fill_lst_env(t_shell *shell, char **envp)
{
	char	str[10000];
	int		i;
	int		j;
	t_env	*new_lst;

	if ((ft_fill_tab_env(shell, envp) < 0))
		return (FAILURE);
	shell->var_env = NULL;
	i = -1;
	while (shell->tab_env[++i])
	{
		ft_bzero(str, ft_strlen(str));
		j = -1;
		new_lst = malloc_lst(shell, sizeof(t_env));
		new_lst->next = NULL;
		while (shell->tab_env[i][++j] && shell->tab_env[i][j] != '=')
			str[j] = shell->tab_env[i][j];
		str[j] = '\0';
		if (!(new_lst->name = ft_strdup(str)) ||
			!(add_lst_to_free(shell, new_lst->name)))
			return (FAILURE);
		new_lst->content = ft_fill_env_content(shell, &shell->tab_env[i][j + 1]);
		if (new_lst->content)
			new_lst->hidden = 0;
		ft_env_add_back(&shell->var_env, new_lst);
	}
	return (SUCCESS);
}
