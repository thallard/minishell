/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 09:47:15 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

char	*ft_get_text_echo(char *txt, t_tree *node)
{
	char		*str;
	int			i;

	if (!(str = malloc(sizeof(char) * (ft_strlen(txt) + 1))))
		return (NULL);
	i = -1;
	while (txt[++i] && txt[i] != '>')
		str[i] = txt[i];
	if (!node->left->item)
		str[i++] = '\n';
	str[i] = '\0';
	return (ft_strtrim(str, " "));
}

int		ft_get_fd(char *txt, t_tree *node, int j, int overwrite)
{
	int				fd;
	char			*path;
	struct stat		fd_status;

	if (!(path = ft_calloc(1, 10000)))
		return (FAILURE);
	while (txt[++j] == ' ')
		;
	if (txt[j] == '/')
		path = ft_strjoin(getcwd(path, 1000), ft_strjoin("/", (txt + j)));
	else
		path = (txt + j);
	//dprintf(1, "debug path = %s\n", path);
	if (stat(path, &fd_status) == -1)
		fd = open(path, O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666);
	else
		if (overwrite)
			fd = open(path, O_WRONLY | O_RDONLY | O_TRUNC, 0666);
		else
			fd = open(path, O_WRONLY | O_RDONLY, 0666);
	return (fd);
}

int		ft_overwrite_in_file(char *txt, t_tree *node, int i, char *str)
{
	struct stat		fd_status;
	char			*path;
	int				fd;
	int				j;

	if ((fd = ft_get_fd(txt, node, i, 1)) < 0)
		return (FAILURE);
	txt[i] = '\0';
	i = -1;
	//dprintf(1, "debug str = %s\n", str);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (SUCCESS);
}

int		ft_add_text_in_file(char *txt, t_tree *node, int i, char *str)
{
	int		fd;

	fd = ft_get_fd(txt, node, i, 0);
	write(fd, str, ft_strlen(str));
	close(fd);
	//ft_printf("debug txt = |%c|%c|\n", txt[i], txt[i + 1]);
	return (fd);
}

int		ft_echo(t_shell *shell, t_tree *node)
{
	int		res;
	int		i;
	char	*str;
	char	*txt;

	txt = ft_calloc(1, 10000);
	i = -1;
	res = 0;
	txt = node->right->item;
	str = ft_get_text_echo(txt, node);
//	dprintf(1, "texte a ecrire : %s\n", str);
	while (txt[++i])
	{
		if (ft_strncmp(&txt[i], ">>", 2) == 0)
			res = ft_add_text_in_file(txt, node, (i = i + 2), str);
		if (txt[i] == '>')
			res = ft_overwrite_in_file(txt, node, i++, str);
	}
	if (!node->left->item)
		str[ft_strlen(str)] = '\n';
	if (!res)
		ft_printf("%s", str);
	return (res);
}