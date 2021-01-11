#include "../../includes/minishell.h"

// char **tab_to_argvnew(char **tab)
// {
// 	char	**argvnew;
// 	int		i;

// 	i = 0;
// 	while (tab[i])
// 		i++;
// 	argvnew = malloc(sizeof(char*) * (i - 1));
// 	i = -1;
// 	while (tab[++i + 1])
// 		argvnew[i] = tab[i + 1];
// 	argvnew[i] = NULL;
// 	return (argvnew);
// }

int	init_shell(t_shell *shell)
{
	// if (shell->ptrs)			a corriger
	// 	free_all_ptr(shell);
	shell->exit = 1;		// bonne valeur ?
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
	return (SUCCESS);
}

int	ft_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	if (!ft_strncmp(node->item, "echo", 5))
		return (ft_echo(shell, node));
	if (!ft_strncmp(node->item, "cd", 3))
		return (ft_cd(shell, node));
	if (!ft_strncmp(node->item, "pwd", 4))
		return (ft_pwd(shell, pipe_fd, is_pipe));
	if (!ft_strncmp(node->item, "export", 7))
	 	return (ft_export(shell, node));
	if (!ft_strncmp(node->item, "unset", 6))
		return (ft_unset(shell, node));
	if (!ft_strncmp(node->item, "env", 4))
		return (ft_env(shell, node));
	if (!ft_strncmp(node->item, "exit", 5))
		ft_exit(shell);
	return (launch_exec(shell, node, pipe_fd, is_pipe));
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
		// ft_print_tree(shell->root, 0); ////////////
		read_tree(shell);
	}
	ft_bzero(buf, ft_strlen(buf));
	return (SUCCESS);
}

int main(int argc, char **argv)
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
	ft_fill_lst_env(shell);

	// ft_print_env_var(shell->var_env); ////

	buf = calloc(1, 1000); // a ajouter a la liste
	if (!buf)
		return (FAILURE);	// exit a gerer avec une erreur
	// size = 1;
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))		// a voir
		return (ft_apply_minishell(shell, argv[2]));
	// ft_printf(1, "minishell-3000$ ");
	while ((size = read(0, buf, 1000) > 0))
		ft_apply_minishell(shell, buf);
	ft_exit(shell);
	return (SUCCESS);
}
