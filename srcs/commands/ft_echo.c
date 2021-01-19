/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:10:09 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 15:32:55 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_get_text_echo(char *txt, t_tree *node, t_shell *shell)
// {
// 	char		str[1000];
// 	int			i;
// 	int			j;
// 	char		*env;

// 	j = -1;
// 	i = -1;
// 	while (ft_strlen(txt) >= ++j && txt[j] && txt[j] != '>' && txt[j] != '<')
// 		if (ft_strncmp(&txt[j], "$?", 2) == 0 && (str[++i] = shell->exit + '0'))
// 			j++;
// 		else if (txt[j] == '$' && txt[j + 1])
// 		{
// 			if (!(env = ft_get_env_value(shell, &txt[j], &j, i)))
// 				continue ;
// 			while (*env)
// 				str[++i] = *env++;
// 		}
// 		else
// 			str[++i] = txt[j];
// 	if (!node->left->item)
// 		str[++i] = '\n';
// 	str[++i] = '\0';
// 	return (ft_strtrim(str, " "));
// }

// int		ft_get_fd(char *txt, t_tree *node, int j, int overwrite)
// {
// 	int				fd;
// 	char			*path;
// 	struct stat		fd_status;
// 	int				i;
// 	char			*new;

// 	(void)node;
// 	path = NULL;
// 	new = ft_strdup(txt);
// 	j = 0;
// 	dprintf(1, "txt vaut = |%s|\n", txt);
// 	while (new[j] && new[j] == ' ')
// 		j++;
// 	i = j;
// 	while (new[i] && new[i] != '<' && new[i] != '>')
// 		i++;
// 	//new = ft_strtrim(new, " ");
// 	dprintf(1, "debug du caractere |%c| et [%s]\n", new[i], new);
// 	new[i] = '\0';
// 	new = ft_strtrim(new, " ");
// 	dprintf(1, "debug new =  |%s|\n", new);
// 	if (txt[j] == '/')
// 		path = ft_strjoin_free(getcwd(path, 1000),
// 				ft_strjoin_free("/", (new), 0, 1), 1, 1);
// 	else
// 		path = ft_strdup(new);
// 	dprintf(1, "debug du path = |%s|\n", path);
// 	if (stat(path, &fd_status) == -1)
// 		fd = open(path, O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666);
// 	else if (overwrite)
// 		fd = open(path, O_WRONLY | O_RDONLY | O_TRUNC, 0666);
// 	else
// 		fd = open(path, O_WRONLY | O_RDONLY, 0666);
// 	free(path);
// 	return (fd);
// }

// int		ft_overwrite_in_file(char *txt, t_tree *node, int i, char *str)
// {
// 	int				fd;

// 	if ((fd = ft_get_fd(txt, node, i, 1)) < 0)
// 		return (FAILURE);
// 			dprintf(1, "debug de txt = |%s|\n", txt);
// 	//txt[i] = '\0';
// 	i = -1;
// 	write(fd, str, ft_strlen(str));
// 	close(fd);
// 	return (SUCCESS);
// }

// int		ft_add_text_in_file(char *txt, t_tree *node, int i, char *str)
// {
// 	int		fd;

// 	fd = ft_get_fd(txt, node, i, 0);
// 	dprintf(1, "debug de txt = %s\n", txt);
// 	write(fd, str, ft_strlen(str));
// 	close(fd);
// 	return (fd);
// }

int		ft_echo(t_shell *shell, char **exec_args, int *tab_null)
{
	int		i;
	int		remove_eol;

	i = 0;
	remove_eol = 0;

//  ft_print_tab_char(exec_args);
// 	dprintf(1, "[%s]\n", exec_args[2]);
	if (!exec_args[1])	// [1]
		ft_printf(1, "\n");
	else
	{
		if (!strncmp(exec_args[1], "-n", 3))
			remove_eol = ++i;
		while (exec_args[++i])
			if (remove_eol != 1 || ft_strncmp(exec_args[i], "-n", 3))
			{
				if (remove_eol != 1 && i > 1 && tab_null[i - 1] && tab_null[i])
					ft_printf(1, " ");
				ft_printf(1, "%s", exec_args[i]);
				remove_eol *= (-1) * remove_eol;
			}
		if (!remove_eol)
				ft_printf(1, "\n");
	}
	shell->exit = 0;
	return (SUCCESS);
}
