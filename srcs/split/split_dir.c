/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:40:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:06:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*create_new_word(t_shell *shell, char **str)
{
	char	*word_part;
	char	*word;

	if (!(word = malloc_lst(shell, 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	word[0] = 0;
	while (**str && **str != ' ' && **str != '<' && **str != '>')
	{
		if (**str != '\'' && **str != '\"')
			word_part = create_new_arg_part_normal(shell, str, NULL, 0);
		else if (**str == '\"')
			word_part = create_new_arg_part_double_quote(shell, str, NULL, 0);
		else
			word_part = create_new_arg_part_simple_quote(shell, str, NULL, 0);
		if (!(word = ft_strjoin(word, word_part)) ||
			!add_lst_to_free(shell, word))
			ft_exit_failure(shell, F_MALLOC, word);
	}
	return (word);
}

static void		create_new_dir(t_shell *shell, char **str,
						t_dir *dir, int *ind)
{
	char	*dir_part;

	if (!(dir[*ind].file = malloc_lst(shell, 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	dir[*ind].file[0] = 0;
	while (**str && **str != ' ' && **str != '<' && **str != '>')
	{
		if (**str != '\'' && **str != '\"')
			dir_part = create_new_dir_part_normal(shell, str, dir, *ind);
		else if (**str == '\"')
			dir_part = create_new_dir_part_double_quote(shell, str, dir, *ind);
		else
			dir_part = create_new_dir_part_simple_quote(shell, str, dir, *ind);
		if (!(dir[*ind].file = ft_strjoin(dir[*ind].file, dir_part)) ||
			!add_lst_to_free(shell, dir[*ind].file))
			ft_exit_failure(shell, F_MALLOC, dir[*ind].file);
	}
	(*ind)++;
}

static int		add_new_dir(t_shell *shell, t_dir *dir, char **str, int *ind)
{
	if (**str != '<' && **str != '>' &&
		(**str != '2' || (*str)[1] != '>'))
		skip_arg(shell, str);
	else
	{
		dir[*ind].dir = is_redirection(str);
		while (**str == ' ')
			(*str)++;
		if (**str == '<' || **str == '>' || **str == ';' || **str == '|'
			|| !**str)
			return (-1);
		if (dir[*ind].dir == 3)
			shell->dir_err = create_new_word(shell, str);
		else
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
	i = 0;
	while (i < (len + 3) / 2)
	{
		dir[i].dir = 0;
		dir[i].file = NULL;
		dir[i++].var = NULL;
	}
	return (dir);
}

t_dir			*split_redirection(t_shell *shell, char *str)
{
	t_dir	*dir;
	int		ind;
	int		err;

	dir = init_dir(shell, str);
	while (*str == ' ')
		str++;
	ind = 0;
	err = 0;
	while (*str && !err)
		err = add_new_dir(shell, dir, &str, &ind);
	if (err == -1)
	{
		shell->char_dir_error = *str;
		return (NULL);
	}
	return (dir);
}
