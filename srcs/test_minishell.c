#include "../includes/minishell.h"

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
	shell->exit = 0;
	shell->var_env = NULL;
	// shell->ptrs = NULL;
	shell->root = NULL;
	shell->input = NULL;
	shell->last_node = SEP;
	shell->op = NULL;
	shell->sep = NULL;
	return (SUCCESS);
}

// int main()
// {
// 	int 	size;
// 	char 	*buf;
// 	char	*newenviron[] = { NULL };
// 	pid_t	program;
// 	t_shell	*shell;
// 	int		res;
// 	char	**tab;

// 	shell = malloc(sizeof(t_shell));
// 	shell->ptrs = NULL;
// 	// init_shell(shell);
// 	buf = calloc(1, 1000);
// 	if (!buf)
// 		return (FAILURE);
// 	size = 1;
// 	while ((size = read(1, buf, 1000) > 0))
// 	{
// 		ft_remove_eol(buf); // 
// 		init_shell(shell);
// 		res = create_main_tree(shell, buf);
// 		ft_printf("res = %d\n\n", res);
// 		ft_print_tree(shell->root, 0);
// 		// if (program == fork()) // A verifier plus tard si c'est viable
// 		// 	execve(ft_remove_eol(tab[0]), tab, newenviron);
// 		// printf("stdin --> %s\n", buf);
// 	}
// 	// go_to_upper_folder();
// }

int main()
{
	int 	size;
	char 	*buf;
	char	**tab;
	char	*newenviron[] = { NULL };
	int		errno;
	pid_t	program;

	buf = calloc(1, 1000);
	if (!buf)
		return (FAILURE);
	size = 1;
	while ((size = read(1, buf, 1000) > 0))
	{
		tab = ft_split(buf, ' ');
		if (program == fork()) // A verifier plus tard si c'est viable
			execve(ft_remove_eol(tab[0]), tab, newenviron);
		// printf("stdin --> %s\n", buf);
	}
	// go_to_upper_folder();
}