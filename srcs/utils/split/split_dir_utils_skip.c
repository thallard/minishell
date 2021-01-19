/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dir_utils_skip.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:59:16 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 17:06:33 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	skip_quotes(t_shell *shell, char **str)
{
	char	c;

	c = **str;
	while (**str && **str != c)
		(*str)++;
	if (!(**str))
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	return (1);
}

// static int	skip_char_redir(t_shell *shell, char **str)
// {
// 	while (!is_redir_quotes_char(**str))
// 		(*str)++;
// 	if (!(**str) || **str == ' ' || **str == '<' || **str == '>')
// 		return (1);
// 	skip_quotes(shell, str);
// 	(*str)++;
// 	skip_char_redir(shell, str);
// 	return (0);
// }

int	skip_arg(t_shell *shell, char **str)
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
