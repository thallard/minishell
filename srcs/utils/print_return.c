/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:45:02 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/12 19:17:24 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		print_unset_error(t_shell *shell, char *cmd)
{
	ft_printf(1, "bash: unset: `%s': not a valid identifier\n", cmd);
	shell->exit = 1;
	return (SUCCESS);
}

int		ft_cmd_not_found(t_shell *shell, char *exec)
{
	(void)shell;					// utilite de shell ?
	ft_printf(1, "bash: %s: command not found\n", exec);	// message a ajuster
	return (SUCCESS);				// valeur a confirmer
}

int		print_cd_error(t_shell *shell, char *cmd)
{
	ft_printf(1, "cd: %s: %s\n", cmd, strerror(errno));
	shell->exit = 1;
	return (SUCCESS);
}

char	*ft_exit_split(char *str)
{
	ft_printf(1, "%s", str);
	return (NULL);
}