/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/03 17:16:58 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_write_in_folder(char **str, int row, char *txt, int flag)
{
	struct stat		fd_status;
	char			*path;
	int				fd;
	
	if (!(path = ft_calloc(1, 10000)))
		return (FAILURE);
	if (str[row + 1][0] != '/')
		path = ft_strjoin(getcwd(path, 10000), ft_strjoin("/", str[row + 1]));
	else
		path = str[row + 1];
	if (stat(path, &fd_status) == -1)
		fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	else
		fd = open(path, O_WRONLY, 0777);
	if (flag)
		txt[ft_strlen(txt)] = '\n';
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
	char	*text_to_write;
	int		k;

	text_to_write = ft_calloc(1, 10000);
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
				res = ft_write_in_folder(argv, j, text_to_write, ft_strncmp(argv[1], "-n", 2));
			else
				text_to_write[++k] = argv[j][i];
		}
	if (ft_strncmp(argv[1], "-n", 2) != 0)
		text_to_write[ft_strlen(text_to_write)] = '\n';
	if (!res)
		ft_printf("%s", text_to_write);
	return (res);
}