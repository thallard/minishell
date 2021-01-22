/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:10:09 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 14:56:37 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_remove_eol_flag(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

static void	print_echo_arg(int *remove_eol, int *print_space, char *arg,
							int var_status)
{
	if (*print_space && var_status)
		ft_printf(1, " ");
	ft_printf(1, "%s", arg);
	if (var_status)
		*print_space = 1;
	*remove_eol *= (-1) * *remove_eol;
}

int			ft_echo(t_shell *shell, char **exec_args, int *tab_null)
{
	int		i;
	int		remove_eol;
	int		print_space;

	i = 0;
	remove_eol = 0;
	print_space = 0;
	if (!exec_args[1])
		ft_printf(1, "\n");
	else
	{
		if (is_remove_eol_flag(exec_args[1]))
			remove_eol = ++i;
		while (exec_args[++i])
			if (remove_eol != 1 || !is_remove_eol_flag(exec_args[i]))
				print_echo_arg(&remove_eol, &print_space, exec_args[i],
								tab_null[i]);
		if (!remove_eol)
			ft_printf(1, "\n");
	}
	shell->exit = 0;
	return (SUCCESS);
}
