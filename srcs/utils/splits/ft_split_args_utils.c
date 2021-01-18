/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:05:42 by thallard          #+#    #+#             */
/*   Updated: 2021/01/18 11:44:51 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		ft_get_nb_env(t_shell *shell, char *str)
{
	int		count;
	int		i;

	(void)shell;
	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '$')
			count++;
	return (count + 1);
}

int		ft_fill_split_env(char *str)
{
	int		i;

	i = 0;
	while (str[++i] && str[i] != '?' && str[i] != ' ' && str[i] != '='
					&& str[i] != '/' && str[i] != '\'' && str[i] != '\"'
					&& str[i] != ';' && str[i] != '$')
		;
	return (i);
}