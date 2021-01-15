/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_op_sep_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:26:03 by thallard          #+#    #+#             */
/*   Updated: 2021/01/15 09:32:44 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		is_separator(char c)
{
	return (c == '|' ||
			c == ';');
}

int		skip_spaces(char **str)
{
	int nb_spaces;

	nb_spaces = 0;
	while (**str == ' ')
	{
		(*str)++;
		nb_spaces++;
	}
	return (nb_spaces);
}

void	str_to_separator(char **str)
{
	while (**str && !is_separator(**str))
		(*str)++;
}

char	*strdup_and_inc_input(t_shell *shell, char **input)
{
	char	*op;
	int		i;
	int		len;

	len = 0;
	if (is_separator((*input)[len]))
		len++;
	else
	{
		while (!is_separator((*input)[len])	&& (*input)[len])
			len++;
	}
	if (!(op = malloc_lst(shell, len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		op[i++] = *((*input)++);
	op[i] = 0;
	return (op);
}
