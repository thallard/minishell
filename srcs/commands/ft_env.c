/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:21:19 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 14:43:02 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_env(t_shell *shell, t_tree *node)
{
	(void) shell;
	ft_printf("je suis dans env %s\n", node->left->item);
	return (SUCCESS);
}

t_env	*ft_env_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}


void	ft_env_add_back(t_env **alst, t_env *new)
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

int		ft_fill_lst_env(t_shell *shell)
{
	char	str[10000];
	int		i;
	int		j;
	t_env	*new_lst;

	
	if ((ft_fill_tab_env(shell) < 0))
		return (FAILURE);
	//ft_fill_first_lst(shell, shell->tab_env, new_lst);
	shell->var_env = NULL;
	i = -1;
	while (shell->tab_env[++i])
	{
		// dprintf(1, "beug de i = %d\n", i);
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
		if (!new_lst->content)
			return (FAILURE);
		//dprintf(1, "%s=%s \n", new_lst->name, new_lst->content);
		//dprintf(1, "debug var env = %p\n", shell->var_env);
		// dprintf(1, "beug de i = %d\n", i);
		ft_env_add_back(&shell->var_env, new_lst);
	}
	return (SUCCESS);
}

t_env	*ft_fill_first_lst(t_shell *shell, char **tab, t_env *lst)
{
	(void)shell;
	(void)lst;
	t_env		*new_lst;
	int			i;
	char		*content;
	int			j;

	if (!(new_lst = malloc_lst(shell, sizeof(t_env))) || !tab[0])
		return (NULL);
	if (!(content = malloc(sizeof(char) * (ft_strlen(tab[0]) + 1))))
		return (NULL);
	i = -1;
	while (tab[0][++i] && tab[0][i] != '=')
		content[i] = tab[0][i];
	content[i] = '\0';
	new_lst->name = content;

	// ft_bzero(content, ft_strlen(content));
	j = -1;
	// while (tab[0][++i])
	// 	content[++j] = tab[0][i];
	// content[j] = '\0';
	// new_lst->content = content;
	dprintf(1, "%s \n", new_lst->name);
	return (new_lst);
}

char	*ft_fill_env_content(t_shell *shell, char *str)
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

int		ft_fill_tab_env(t_shell *shell)
{
	int				fd;
	char			str_file[10000];
	struct stat		fd_status;

	if (stat("env_file", &fd_status) == -1)
		return (FAILURE);
	fd = open("env_file", O_RDONLY);
	read(fd, str_file, 10000);
	if (!(shell->tab_env = ft_split(str_file, '\n')))
		return (FAILURE);
	if (!(add_lst_to_free(shell, shell->tab_env)))
		return (FAILURE);
	return (SUCCESS);
}

