#include "../includes/minishell.h"

void	*add_lst_to_free(t_shell *shell, void *ptr)
{
	t_list	*elem;

	if (!(elem = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&shell->ptrs, elem);
	return (ptr);
}

void	*malloc_lst(t_shell *shell, int size) // penser a bien initialiser shell-ptrs
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!add_lst_to_free(shell, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

int		free_all_ptr(t_shell *shell)
{
	ft_lstclear(&shell->ptrs, free);
	return (0);
}

// int		free_line(char **line, int err)
// {
// 	if (*line)
// 	{
// 		free(*line);
// 		*line = NULL;
// 	}
// 	return (err);
// }
