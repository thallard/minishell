/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/04 11:54:04 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_add_txt_in_file(char *txt, int fd)
{
	int		i;
	char	*str;
	char	buf[100];

	str = ft_strdup("");
	i = -1;
	while (read(fd, buf, 100) > 0)
		str = ft_strjoin(str, buf);
	return (SUCCESS);
}

int		ft_overwrite_in_file(char **str, int row, char *txt, int flag)
{
	struct stat		fd_status;
	char			*path;
	int				fd;


	if (!(path = ft_calloc(1, 10000)))
		return (FAILURE);
	if (str[++row][0] != '/')
		path = ft_strjoin(getcwd(path, 10000), ft_strjoin("/", str[row]));
	else
		path = str[row];
	if (stat(path, &fd_status) == -1)
		fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	else
		fd = open(path, O_WRONLY, 0777);
	if (flag)
		txt[ft_strlen(txt)] = '\n';
	if (!ft_strncmp(str[row], ">>", 2))
		return (ft_add_txt_in_file(txt, fd));
	dprintf(1, "debug path = %s\n", txt);
	write(fd, txt, ft_strlen(txt));
	close(fd);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	int		res;
	int		j;
	int		i;
	char	*txt;
	int		k;

	txt = ft_calloc(1, 10000);
	j = 0;
	res = 0;
	k = -1;
	while (argv[++j] && (i = -1) == -1)
		while (argv[j][++i])
		{
			if (ft_strncmp(argv[j], "-n", 2) == 0 && i == 0)
			{
				dprintf(1, "if = %s\n", argv[j]);
				j++;
				i = -1;
			}
			else if (argv[j][i] == '>')
				res = ft_overwrite_in_file(argv, j, txt, ft_strncmp(argv[1], "-n", 2));
			else if (!res)
				txt[++k] = argv[j][i];
		}
	if (ft_strncmp(argv[1], "-n", 2) != 0)
		txt[ft_strlen(txt)] = '\n';
	if (!res)
		ft_printf("%s", txt);
	return (res);
}