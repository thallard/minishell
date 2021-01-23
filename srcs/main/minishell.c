/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:32:26 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 14:08:17 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_shell(t_shell *shell, int begin)
{
	if (begin)
	{
		shell->var_env = NULL;
		shell->tab_env = NULL;
		shell->buffer_std = NULL;
		shell->exit = 0;
	}
	shell->split->s_quotes = 0;
	shell->split->d_quotes = 0;
	shell->root = NULL;
	shell->input = NULL;
	shell->last_node = SEP;
	shell->op = NULL;
	shell->sep = NULL;
	shell->last_pipe = 1;
	if ((shell->std[0] = dup(STDIN_FILENO)) == -1 ||
		(shell->std[1] = dup(STDOUT_FILENO)) == -1 ||
		(shell->std[2] = dup(STDERR_FILENO)) == -1)
		print_error_and_exit(shell, "dup", -1);
	shell->lst_fd = NULL;
	shell->split->env = 0;
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	shell->dir_err = NULL;
	shell->lst_var_len = NULL;
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

static void	ft_launch_tree(t_shell *shell)
{
	int res;

	init_shell(shell, 0);
	if (ft_strlen(shell->buffer_std) > 0)
	{
		res = create_main_tree(shell, shell->buffer_std);
		if (res == DOUBLE_SEP_V || res == DOUBLE_SEP_DV ||
			res == DOUBLE_SEP_P || res == DOUBLE_SEP_DP ||
			res == CHAR_DIR_ERR)
			print_sep_error(shell, res);
		if (res >= 0)
			read_tree(shell);
	}
	shell->buffer_std = NULL;
}

static int	ft_apply_minishell(t_shell *shell, char *buf)
{
	int	len;

	len = ft_bufferlen(buf, -1);
	if (len != 0)
	{
		buf[ft_abs(len)] = 0;
		if (shell->buffer_std)
			shell->buffer_std = ft_strjoin(shell->buffer_std, buf);
		else
			shell->buffer_std = ft_strdup(buf);
		if (!shell->buffer_std || !(add_lst_to_free(shell, shell->buffer_std)))
			ft_exit_failure(shell, F_MALLOC, shell->buffer_std);
	}
	if (len > 0 || buf[0] == '\n')
	{
		ft_launch_tree(shell);
		print_header(shell->std[1]);
	}
	ft_memset(buf, -1, 10000);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_shell	*shell;

	if (!(shell = malloc(sizeof(t_shell))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	shell->lst_fd = NULL;
	shell->ptrs = NULL;
	if (!(shell->split = malloc_lst(shell, sizeof(t_split))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	init_shell(shell, 1);
	ft_fill_lst_env(shell, envp);
	if (!(buf = ft_calloc(1, 10000)) || !add_lst_to_free(shell, buf))
		ft_exit_failure(shell, F_MALLOC, buf);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		return (ft_apply_minishell(shell, argv[2]));
	print_header(shell->std[1]);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrl_c);
	ft_memset(buf, -1, 10000);
	while (read(0, buf, 10000) > 0 || shell->buffer_std)
		ft_apply_minishell(shell, buf);
	ft_exit_failure(shell, 0, NULL);
	return (SUCCESS);
}
