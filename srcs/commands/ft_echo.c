/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by thallard          #+#    #+#             */
/*   Updated: 2021/01/03 15:09:01 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_write_in_folder(char **str, int row, char *txt)
{
	int		fd;
	fd = open(str[row + 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	write(fd, txt, ft_strlen(txt));
	close(fd);
	return (1);
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
	k = -1;
	while (argv[++j] && (i = -1) == -1)
		while (argv[j][++i])
		{	
			if (argv[j][i] == '>')
				ft_write_in_folder(argv, j, text_to_write);
			else
				text_to_write[++k] = argv[j][i];
		}
	ft_printf("%s\n", text_to_write);
	res = 0;
	return (res);
}