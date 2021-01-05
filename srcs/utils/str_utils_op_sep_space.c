/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_op_sep_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:26:03 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 15:26:03 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		is_operand(char *str)
{
	if(!ft_strncmp(str, "echo", 5))
		return (4);			// necessaire plutot que '1' ?
	if (!ft_strncmp(str, "cd", 3))
		return (2);
	if (!ft_strncmp(str, "pwd", 4))
		return (3);
	if (!ft_strncmp(str, "export", 7))
		return (6);
	if (!ft_strncmp(str, "unset", 6))
		return (5);
	if (!ft_strncmp(str, "env", 4))
		return (3);
	if (!ft_strncmp(str, "exit", 5))
		return (4);
	return (0);
}

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
		while ((*input)[len] != ' ' && !is_separator((*input)[len])
			&& (*input)[len])
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