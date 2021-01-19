/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:40:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 17:36:42 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	add_new_dir(t_shell *shell, t_dir *dir, char **str, int *ind)
{
// dprintf(1, "str = |%s|\n", *str);

	if (**str != '<' && **str != '>')
		skip_arg(shell, str);
	else
	{

// dprintf(1, "p1 str |%s|\n", *str);

		dir[*ind].dir = 1;
		if (**str == '<')
			dir[*ind].dir = -1;
		if (**str == '>' && (*str)[1] == '>' && (*str)++)
			dir[*ind].dir = 2;
		(*str)++;
		while (**str == ' ')
			(*str)++;
		create_new_dir(shell, str, dir, ind);
	}
	while (**str == ' ')
		(*str)++;
	return (0);
}

static t_dir	*init_dir(t_shell *shell, char *str)
{
	t_dir	*dir;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!(dir = malloc_lst(shell, sizeof(t_dir) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	// if (!(dir->var = malloc_lst(shell, sizeof(t_var_status*) * (len + 3) / 2)))
	// 	ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	while (i < (len + 3) / 2)
	{
		dir[i].dir = 0;
		dir[i].file = NULL;
		dir[i++].var = NULL;
	}
	return (dir);
}

t_dir	*split_redirection(t_shell *shell, char *str)
{
	t_dir	*dir;
	int		ind;

	if (!str)
		return (NULL);
	dir = init_dir(shell, str);
	while (*str == ' ')
		str++;
	ind = 0;
	while (*str)
		add_new_dir(shell, dir, &str, &ind);
	return (dir);
}
