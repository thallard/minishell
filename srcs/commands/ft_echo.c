/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/04 18:53:17 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

// int		ft_add_txt_in_file(char *txt, int fd)
// {
// 	int		i;
// 	char	*str;
// 	char	buf[100];

// 	if (!(str = ft_strdup("")))
// 		return (FAILURE);
// 	i = -1;
// 	while (read(fd, buf, 100) > 0)
// 		str = ft_strjoin(str, buf);
// 	dprintf(1, "STR = %s\n", str);
// 	return (SUCCESS);
// }

char	*ft_get_text_echo(char *txt, t_tree *node, int i)
{
	char	*str;
	int		j;

	if (!(str = malloc(sizeof(char) * (ft_strlen(txt + 10)))))
		return (NULL);
	j = 9;
	while (txt[--j] && txt[j] == ' ')
		dprintf(1, "caractere a %d et %c\n", j, txt[j]);
	dprintf(1, "debug de j %d\n", j);
	i = -1;
	while (txt[++i] && i < j)
		txt[i] = str[i];
	return (str);
}

int		ft_overwrite_in_file(char *txt, t_tree *node, int i)
{
	struct stat		fd_status;
	char			*path;
	int				fd;
	int				j;
	char			new_txt[1000];

	j = i;
	if (!(path = ft_calloc(1, 10000)))
		return (FAILURE);
	while (txt[++j] == ' ')
		;
	if (txt[j] == '/')
		path = ft_strjoin(getcwd(path, 1000), ft_strjoin("/", (txt + j)));
	else
		path = (txt + j);
	dprintf(1, "debug path = %s\n", path);
	if (stat(path, &fd_status) == -1)
		fd = open(path, O_CREAT | O_WRONLY | O_RDONLY, 0666);
	else
		fd = open(path, O_WRONLY | O_RDONLY, 0666);
			dprintf(1, "debug txt = %c\n", txt[i]);
	txt[i] = '\0';
	i = -1;
	while (txt[++i] && txt[i] != ' ')
		new_txt[i] = txt[i];
	new_txt[i] = '\0';
	if (!node->left->item)
		new_txt[ft_strlen(new_txt)] = '\n';
	dprintf(1, "debug new_txt = %s\n", new_txt);
	write(fd, new_txt, ft_strlen(new_txt));
	close(fd);
	return (SUCCESS);
}

int		ft_echo(t_shell *shell, t_tree *node)
{
	int		res;
	int		j;
	int		i;
	char	*txt;
	int		k;

	txt = ft_calloc(1, 100);
	i = -1;
	res = 0;
	txt = node->right->item;
	while (txt[++i])
	{
		if (txt[i] == '>')
			res = ft_overwrite_in_file(txt, node, i);
	}
	if (!node->left->item)
		txt[ft_strlen(txt)] = '\n';
	if (!res)
		ft_printf("%s", txt);

	return (res);
}