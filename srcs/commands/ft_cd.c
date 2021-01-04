/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:08:51 by thallard          #+#    #+#             */
/*   Updated: 2021/01/03 15:08:51 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_to_upper_folder(void)
{
	char	*current_path;
	char	*upper_path;
	int		indice;

	current_path = calloc(1, 500);
	upper_path = NULL;

	getcwd(current_path, 1000);
	if (!current_path)
	{
		ft_printf("current_path NULL\n");
		return (-1);
	}
	ft_printf("\ncurrent_path = %s\n", current_path);

	indice = ft_strrfind(current_path, '/');
	if (indice > 0)
		upper_path = ft_substr(current_path, 0, indice);
	else
		upper_path = current_path;
	chdir(upper_path);
	ft_free_ptr(current_path);
	current_path = upper_path;
	getcwd(current_path, 1000);
	ft_printf("current_path = %s\n", current_path);

	return (SUCCESS);
}

int	go_to_folder(char *folder)
{
	char	*current_path;
	char	*path;
	int		res;

	current_path = calloc(1, 500);
	getcwd(current_path, 1000);
	if (!current_path)
	{
		ft_printf("current_path NULL\n");
		return (-1);
	}
	ft_printf("\ncurrent_path = %s\n", current_path);
	path = ft_strjoin(current_path, "/");
	path = ft_strjoin(path, folder);
	path = ft_strtrim(path, "\n");
	res = chdir(path);
	getcwd(current_path, 1000);
	ft_printf("current_path = %s\n", current_path);

	return (res);
}

int		ft_cd(char **tab, t_tree *node, t_shell *shell)
{
	int		res;

	tab[1] = ft_strtrim(tab[1], "\n");
	if (!ft_strncmp(tab[1], "..", 3))
		res = go_to_upper_folder();
	else
		res = go_to_folder(tab[1]);

	ft_printf("res = %d\n", res);

	return (res);

}