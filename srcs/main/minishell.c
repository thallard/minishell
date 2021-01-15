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

static int	ft_bufferlen(char *str, char c)
{
	int i;
	int sign;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != c && str[i] && str[i] != '\n')
		i++;
	sign = 1;
	if (str[i] == c)
		sign = -1;
	return (i * sign);
}

int		ft_apply_minishell(t_shell *shell, char *buf)
{
	int	res;
	int	len;

	len = ft_bufferlen(buf, -1);	// a voir quel char
	if (len != 0)
	{
		buf[ft_abs(len)] = 0;
		if (shell->buffer_std)
			shell->buffer_std = ft_strjoin(shell->buffer_std, buf);
		else
			shell->buffer_std = ft_strdup(buf);
		if (!shell->buffer_std || !(add_lst_to_free(shell, shell->buffer_std)))
			return (ft_free_ptr(shell->buffer_std));	// a gerer
	}
	if (len > 0)
	{
		//ft_printf(1, "minishell$ ");
		ft_remove_eol(buf);
		init_shell(shell);
		res = create_main_tree(shell, shell->buffer_std);
		if (res == DOUBLE_SEP)
			ft_printf(1, "syntax error near unexpected token `%s'\n", shell->sep); // a ajuster
		if (res >= 0)
		{
			// ft_print_tree(shell->root, 0); ////////////////////////
			read_tree(shell);
		}
		shell->buffer_std = NULL;
	}
	ft_memset(buf, -1, 10000);		// a voir quel char
	return (SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	int 	size;
	char 	*buf;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->split = malloc(sizeof(t_split));
	shell->ptrs = NULL; 
	shell->var_env = NULL;
	shell->tab_env = NULL;
	shell->buffer_std = NULL;
	init_shell(shell);

	ft_fill_lst_env(shell, envp);

	// ft_print_env_var(shell->var_env); ////
	if (!(buf = ft_calloc(1, 10000)) || !add_lst_to_free(shell, buf))
		return (FAILURE); // a ajouter a la liste // exit a gerer avec une erreur
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))		// a voir
		return (ft_apply_minishell(shell, argv[2]));

	// ft_printf(1, "minishell$ ");

	// signal(SIGINT,SIG_DFL);
	// signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGINT, &ft_ctrl_c);
	
	ft_memset(buf, -1, 10000);		// a voir quel char
	while ((size = read(0, buf, 10000) > 0) || shell->buffer_std)
		ft_apply_minishell(shell, buf);
	ft_exit(shell, ft_split_args_quotes(shell, "0"), shell->tab_env);
	return (SUCCESS);
}


/*
int		ft_apply_minishell(t_shell *shell, char *buf)
{
	int	res;

	//ft_printf(1, "minishell$ ");
	ft_remove_eol(buf);
	init_shell(shell);
	res = create_main_tree(shell, buf);
	if (res == DOUBLE_SEP)
		ft_printf(1, "syntax error near unexpected token `%s'\n", shell->sep); // a ajuster
	if (res >= 0)
	{
		// ft_print_tree(shell->root, 0); ////////////////////////
		read_tree(shell);
	}
	ft_bzero(buf, ft_strlen(buf));
	return (SUCCESS);
}
*/