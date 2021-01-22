/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:00:53 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:05:29 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_arg_part_double_quote(char **str, char *arg_part)
{
	int	i;

	i = 0;
	(*str)++;
	while (**str != '\"')
	{
		if (**str == '\\' && (*str)[1] == '$' && ((*str)[1] = -36))
			(*str)++;
		else if (**str == '\\' && ((*str)[1] == '\"' || (*str)[1] == '\\'))
			(*str)++;
		arg_part[i++] = *((*str)++);
	}
	arg_part[i] = 0;
	(*str)++;
}

int		is_redirection(char **str)
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
