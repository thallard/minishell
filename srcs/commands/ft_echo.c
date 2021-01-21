/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:10:09 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/21 11:01:45 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	change_last_arg_env(t_shell *shell, char **exec_args)
{
	int		i;
	char	*str;
	
	i = 0;
	while (exec_args[i + 1])
		i++;
	if (!(str = ft_strdup(exec_args[i])) || !add_lst_to_free(shell, str))
		ft_exit_failure(shell, F_MALLOC, str);
	replace_env_content(shell, "_", str, 0);	
}

static	int	is_remove_eol_flag(char *str)
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

int		ft_echo(t_shell *shell, char **exec_args, int *tab_null)
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
	change_last_arg_env(shell, exec_args);
	return (SUCCESS);
}
