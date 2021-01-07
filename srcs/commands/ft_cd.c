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

static int	get_correct_return(int res)
{
	if (res == -1)
		return (-1);
	return (SUCCESS);
}

static char	*build_path(char *current_path, char *folder)
{
char	*path_temp;
char	*path;

	if (!(path = ft_strjoin(current_path, "/")))
		return (NULL);
	path_temp = path;
	path = ft_strjoin(path, folder);
	free(path_temp);
	if (!path)
		return (NULL);
	path_temp = path;
	path = ft_strtrim(path, "\n");
	free(path_temp);
	return (path);
}

static int	go_to_upper_folder(void)
{
	char	*current_path;
	char	*path_temp;
	char	*upper_path;
	int		indice;
	int		res;

	if (!(current_path = ft_calloc(1, 500)))
		return (-1);
	upper_path = NULL;
	path_temp = current_path;
	getcwd(current_path, 1000);
	if (!current_path)
		return (ft_free_ptr(path_temp));
	indice = ft_strrfind(current_path, '/');
	if (indice > 0)
		upper_path = ft_substr(current_path, 0, indice);
	else
		upper_path = current_path;
	res = chdir(upper_path);
	if (current_path != upper_path)
		ft_free_ptr(upper_path);
	ft_free_ptr(current_path);
	if (res == -1)
		return (-1);
	return (SUCCESS);
}

static int	go_to_folder(char *folder)
{
	char	*current_path;
	char	*path_temp;
	char	*path;
	int		res;

	current_path = NULL;
	if (folder[0] == '/')
	{
		if (!(path = ft_strdup(folder)))
			return (-1);
	}
	else
	{
		if (!(current_path = ft_calloc(1, 500)))
			return (-1);
		path_temp = current_path;
		if (!(getcwd(current_path, 1000)))
			return (ft_free_ptr(path_temp));
		else if (!(path = build_path(current_path, folder)))
			return (-1);
	}
	res = chdir(path);
	ft_free_ptr(current_path);
	ft_free_ptr(path);
	return (get_correct_return(res));
}

static int	go_to_home(t_shell *shell)
{
	char	*path;
	int		res;

	path = NULL;
	if ((get_var_env(shell, "HOME", &path) == -1) || !path)
		return (-1);
	res = chdir(path);
	return (get_correct_return(res));
}

int		ft_cd(t_shell *shell, t_tree *node)
{
	int		res;

	if (!node->left->item)
		res = go_to_home(shell);
	else if (!ft_strncmp(node->left->item, "..", 3))
		res = go_to_upper_folder();
	else
		res = go_to_folder(node->left->item);
	if (res == -1)
		return (print_cd_error(shell, node->left->item));
	return (SUCCESS);
}
