/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:30:13 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:30:52 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		print_oldpwd_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: %s: OLDPWD not set\n", cmd);
	shell->exit = 0;
	return (SUCCESS);
}

int		print_unset_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", cmd);
	shell->exit = 1;
	return (SUCCESS);
}

int		ft_cmd_not_found(t_shell *shell, char *exec, t_tree *node)
{
	manage_redirection(shell, node->dir);
	ft_printf(STDERR_FILENO, "minishell: %s: command not found\n", exec);
	shell->exit = 127;
	reset_stds(shell);
	return (SUCCESS);
}

int		find_sep_error(char *str)
{
	char	sep;
	int		i;

	sep = str[0];
	i = 1;
	while (str[i] == ' ')
		i++;
	if (is_separator(str[i]) && str[i] == sep)
	{
		if (sep == ';')
			return (DOUBLE_SEP_DV);
		else
			return (DOUBLE_SEP_DP);
	}
	if (sep == ';')
		return (DOUBLE_SEP_V);
	else
		return (DOUBLE_SEP_P);
}

int		print_sep_error(t_shell *shell, int err)
{
	if (err == DOUBLE_SEP_DV)
		ft_printf(STDERR_FILENO, "syntax error near unexpected token `;;'\n");
	else if (err == DOUBLE_SEP_V)
		ft_printf(STDERR_FILENO, "syntax error near unexpected token `;'\n");
	else if (err == DOUBLE_SEP_P)
		ft_printf(STDERR_FILENO, "syntax error near unexpected token `|'\n");
	else if (err == DOUBLE_SEP_DP)
		ft_printf(STDERR_FILENO, "syntax error near unexpected token `||'\n");
	shell->exit = 258;
	if (err == CHAR_DIR_ERR)
	{
		if (shell->char_dir_error)
			ft_printf(STDERR_FILENO,
				"syntax error near unexpected token `%c'\n",
				shell->char_dir_error);
		else
			ft_printf(STDERR_FILENO,
				"syntax error near unexpected token `newline'\n");
		shell->exit = 2;
	}
	return (SUCCESS);
}
