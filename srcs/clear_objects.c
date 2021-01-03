#include "../includes/minishell.h"

void	*malloc_lst(t_shell *shell, int size) // penser a bien initialiser shell-ptrs
{
	void	*ptr;
	t_list	*elem;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!(elem = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&shell->ptrs, elem);
	return (ptr);
}

// int		malloc_trim_lst(t_game *game, char *s1, char c)
// {
// 	char	*ptr;
// 	t_list	*elem;

// 	if ((c == 'N' && game->window.map_info.path_no) ||
// 		(c == 'S' && game->window.map_info.path_so) ||
// 		(c == 'E' && game->window.map_info.path_ea) ||
// 		(c == 'W' && game->window.map_info.path_we) ||
// 		(c == 's' && game->window.map_info.path_sprite))
// 		return (-12);
// 	if (!(ptr = ft_strtrim(s1, " ")))
// 		return (-8);
// 	if (!(elem = ft_lstnew(ptr)))
// 		return (free_error_int(ptr, -8));
// 	ft_lstadd_back(&game->ptrs, elem);
// 	if (c == 'N')
// 		game->window.map_info.path_no = ptr;
// 	if (c == 'S')
// 		game->window.map_info.path_so = ptr;
// 	if (c == 'E')
// 		game->window.map_info.path_ea = ptr;
// 	if (c == 'W')
// 		game->window.map_info.path_we = ptr;
// 	if (c == 's')
// 		game->window.map_info.path_sprite = ptr;
// 	return (2);
// }

int		free_all_ptr(t_shell *shell)
{
	ft_lstclear(&shell->ptrs, free);
	clear_session_images(shell);
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
