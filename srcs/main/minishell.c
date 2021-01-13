/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:31:50 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 13:31:50 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_shell(t_shell *shell)
{
	// if (shell->ptrs)			a corriger
	// 	free_all_ptr(shell);
	shell->exit = 0;		// bonne valeur ?
	//shell->var_env = NULL;
	// shell->tab_env = NULL;
	// shell->ptrs = NULL;
	shell->split->s_quotes = 0;
	shell->split->d_quotes = 0;
	shell->root = NULL;
	shell->input = NULL;
	shell->last_node = SEP;
	shell->op = NULL;
	shell->sep = NULL;
	shell->last_pipe = 1;
	shell->std[0] = dup(STDIN_FILENO);
	shell->std[1] = dup(STDOUT_FILENO);
	shell->lst_fd = NULL;
	return (SUCCESS);
}

int		ft_apply_minishell(t_shell *shell, char *buf)
{
	int	res;

	//ft_printf(1, "minishell-3000$ ");
	ft_remove_eol(buf);
	init_shell(shell);
	res = create_main_tree(shell, buf);
	if (res == -2)
		ft_printf(1, "syntax error near unexpected token `%s'\n", shell->sep);
	if (res >= 0)
	{
		// ft_print_tree(shell->root, 0); ////////////////////////
		read_tree(shell);
	}
	ft_bzero(buf, ft_strlen(buf));
	return (SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	int 	size;
	char 	*buf;
	t_shell	*shell;
	// int		res;

// int	err = 2;
// ft_printf(1, "err = %d\nerror = %s", err, strerror(err));

	shell = malloc(sizeof(t_shell));
	shell->split = malloc(sizeof(t_split));
	shell->ptrs = NULL; 
	shell->var_env = NULL;
	shell->tab_env = NULL;
	// init_shell(shell);
	// ft_fill_lst_env(shell);
	// int i;

	// i = -1;
	// while (envp[++i])
	// 	ft_printf(1, "ENV : %s\n", envp[i]);
	ft_fill_lst_env(shell, envp);

	// ft_print_env_var(shell->var_env); ////

	if (!(buf = malloc_lst(shell, 10000)))
		return (FAILURE); // a ajouter a la liste // exit a gerer avec une erreur
	// size = 1;
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))		// a voir
		return (ft_apply_minishell(shell, argv[2]));
	// ft_printf(1, "minishell-3000$ ");
	while ((size = read(0, buf, 10000) > 0))
		ft_apply_minishell(shell, buf);
	// ft_exit(shell, PARENT);
	return (SUCCESS);
}
