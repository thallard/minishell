/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils_skip.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:59:16 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 12:43:23 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_redir_quotes_char(char c)
{
	if (!c || c == ' ' || c == '<' || c == '>' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

int			skip_quotes(t_shell *shell, char **str)
{
	char	c;

	c = **str;
	while (**str && **str != c)
	{
		if (**str == '\\' && (*str)[1])
			(*str)++;
		(*str)++;
	}
	if (!(**str))
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	return (1);
}

static int	skip_char_redir(t_shell *shell, char **str)
{
	while (!is_redir_quotes_char(**str))
		(*str)++;
	if (!(**str) || **str == ' ' || **str == '<' || **str == '>')
		return (1);
	skip_quotes(shell, str);
	(*str)++;
	skip_char_redir(shell, str);
	return (0);
}

int			skip_redir(t_shell *shell, char **str)
{
	if ((*str)[0] == '>' && (*str)[1] == '>')
		(*str)++;
	(*str)++;
	while (**str == ' ')
		(*str)++;
	skip_char_redir(shell, str);
	return (1);
}

int			skip_arg(t_shell *shell, char **str)
{
	while (!is_redir_quotes_char(**str))
		(*str)++;
	if (!(**str) || **str == ' ' || **str == '<' || **str == '>')
		return (1);
	skip_quotes(shell, str);
	(*str)++;
	skip_arg(shell, str);
	return (0);
}
