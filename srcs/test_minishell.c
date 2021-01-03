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
	free_all_ptr(shell);
	shell->exit = 0;
	shell->var_env = NULL;
	shell->ptrs = NULL;
	shell->root = NULL;
	shell->input = NULL;
	shell->last_node = SEP;
	return (SUCCESS);
}

int main()
{
	int 	size;
	char 	*buf;
	char	*newenviron[] = { NULL };
	pid_t	program;
	t_shell	*shell;
	int		res;

	buf = calloc(1, 1000);
	if (!buf)
		return (FAILURE);
	size = 1;
	while ((size = read(1, buf, 1000) > 0))
	{
		init_shell(shell);
		create_main_tree(shell, buf);

		// if (program == fork()) // A verifier plus tard si c'est viable
			// execve(ft_remove_eol(tab[0]), tab, newenviron);
		// printf("stdin --> %s\n", buf);
	}
	// go_to_upper_folder();
}

// int main()
// {
// 	int 	size;
// 	char 	*buf;
// 	char	**tab;
// 	char	*newenviron[] = { NULL };
// 	int		errno;
// 	pid_t	program;

// 	buf = calloc(1, 1000);
// 	if (!buf)
// 		return (FAILURE);
// 	size = 1;
// 	while ((size = read(1, buf, 1000) > 0))
// 	{
// 		tab = ft_split(buf, ' ');
// 		if (program == fork()) // A verifier plus tard si c'est viable
// 			execve(ft_remove_eol(tab[0]), tab, newenviron);
// 		// printf("stdin --> %s\n", buf);
// 	}
// 	// go_to_upper_folder();
// }