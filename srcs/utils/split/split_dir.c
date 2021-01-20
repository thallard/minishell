/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:40:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/20 09:07:23 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_redirection(char **str)
{
	if (**str == '>' && (*str)[1] == '>')
	{
		*str += 2;
		return (2);
	}
	else if (**str == '2' && (*str)[1] == '>')
	{
		(*str) += 2;
		return (3);
	}
	else if (**str == '>')
	{
		(*str)++;
		return (1);
	}
	else if (**str == '<')
	{
		(*str)++;
		return (-1);
	}
	return (0);
}

static char	*create_new_word(t_shell *shell, char **str)
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

static int	add_new_dir(t_shell *shell, t_dir *dir, char **str, int *ind)
{
	if (**str != '<' && **str != '>' &&
		(**str != '2' || (*str)[1] != '>'))
		skip_arg(shell, str);
	else
	{
		dir[*ind].dir = is_redirection(str);		
		while (**str == ' ')
			(*str)++;
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
