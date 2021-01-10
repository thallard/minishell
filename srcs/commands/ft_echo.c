/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/10 15:53:35 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_text_echo(char *txt, t_tree *node, t_shell *shell)
{
	char		str[1000];
	int			i;
	int			j;
	char		*env;

	j = -1;
	i = -1;
	while (ft_strlen(txt) >= ++j && txt[j] && txt[j] != '>' && txt[j] != '<')
		if (ft_strncmp(&txt[j], "$?", 2) == 0 && (str[++i] = shell->exit + '0'))
			j++;
		else if (txt[j] == '$' && txt[j + 1])
		{
			if (!(env = ft_get_env_value(shell, &txt[j], &j, i)))
				continue ;
			while (*env)
				str[++i] = *env++;
		}
		else
			str[++i] = txt[j];
	if (!node->left->item)
		str[++i] = '\n';
	str[++i] = '\0';
	return (ft_strtrim(str, " "));
}

int		ft_get_fd(char *txt, t_tree *node, int j, int overwrite)
{
	int				fd;
	char			*path;
	struct stat		fd_status;
	int				i;
	char			*new;

	(void)node;
	path = NULL;
	new = ft_strdup(txt);
	j = 0;
	dprintf(1, "txt vaut = |%s|\n", txt);
	while (new[j] && new[j] == ' ')
		j++;
	i = j;
	while (new[i] && new[i] != '<' && new[i] != '>')
		i++;
	//new = ft_strtrim(new, " ");
	dprintf(1, "debug du caractere |%c| et [%s]\n", new[i], new);
	new[i] = '\0';
	new = ft_strtrim(new, " ");
	dprintf(1, "debug new =  |%s|\n", new);
	if (txt[j] == '/')
		path = ft_strjoin_free(getcwd(path, 1000),
				ft_strjoin_free("/", (new), 0, 1), 1, 1);
	else
		path = ft_strdup(new);
	dprintf(1, "debug du path = |%s|\n", path);
	if (stat(path, &fd_status) == -1)
		fd = open(path, O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666);
	else if (overwrite)
		fd = open(path, O_WRONLY | O_RDONLY | O_TRUNC, 0666);
	else
		fd = open(path, O_WRONLY | O_RDONLY, 0666);
	free(path);
	return (fd);
}

int		ft_overwrite_in_file(char *txt, t_tree *node, int i, char *str)
{
	int				fd;

	if ((fd = ft_get_fd(txt, node, i, 1)) < 0)
		return (FAILURE);
			dprintf(1, "debug de txt = |%s|\n", txt);
	//txt[i] = '\0';
	i = -1;
	write(fd, str, ft_strlen(str));
	close(fd);
	return (SUCCESS);
}

int		ft_add_text_in_file(char *txt, t_tree *node, int i, char *str)
{
	int		fd;

	fd = ft_get_fd(txt, node, i, 0);
	dprintf(1, "debug de txt = %s\n", txt);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (fd);
}

int		ft_echo(t_shell *shell, t_tree *node)
{
	int		res;
	int		i;
	char	**tab;

	i = -1;
	res = 0;
	// txt = node->right->item;
	// if (!txt)
	// {
	// 	if (!node->left->item)
	// 		ft_printf(1, "\n");
	// 	else
	// 		ft_printf(1, "\0");
	// 	shell->exit = 0;
	// 	free(txt);
	// 	return (SUCCESS);
	// }
	// if (txt)
	// 	str = ft_get_text_echo(txt, node, shell);
	tab = ft_split_quotes(shell, shell->split, node->right->item);
		i = -1;
	while (tab[++i])
	{ft_printf(1, "%s", tab[i]);
		if (tab[i + 1])
			ft_printf(1, " ");
	}
	if (!node->left->item)
	ft_printf(1, "|\n");
	shell->exit = 0;
	// 		//dprintf(1, "debug du txt sortie de get echo text = %s\n", txt);
	// while (txt[++i])
	// {
	// 	if (ft_strncmp(&txt[i], ">>", 2) == 0 &&
	// 	(res = ft_add_text_in_file(&txt[i], node, (i + 2), str)))
	// 		i = i + 2;
	// 	if (txt[i] == '>')
	// 	{
	// 		dprintf(1, "debug du txt avec le > = %s\n", &txt[i]);
	// 		res = ft_overwrite_in_file(&txt[i + 1], node, i, str);
	// 		i++;
	// 	}
	// 	if (txt[i] == '<')
	// 	{
	// 		// while (txt[++i] && txt[i] != '>' && txt[i] != '<' && txt[i + 1])
	// 		// 	;
	// 	}
	// 		//dprintf(1, "Chaque caractere a i : %d et le caractere %c\n", i, txt[i]);
	// }
	// if (!res)
	// 	ft_printf(1, "%s", str);
	// free(str);
	// free(txt);
	return (res);
}
