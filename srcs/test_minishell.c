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