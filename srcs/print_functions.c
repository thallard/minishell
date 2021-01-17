#include "../includes/minishell.h"

void	print_nb_char(int nb, char c)
{
	int i;

	i = -1;
	while (++i < 4 * nb)
		write(1, &c, 1);
}

void	ft_print_tree(t_tree *node, int nb)
{
	if (!node)
	{
		print_nb_char(nb, ' ');
		ft_printf(1, "0\n");
	}
	else
	{
		print_nb_char(nb, ' ');
		ft_print_tab_char(node->args->args);

		print_nb_char(nb, '-');
		ft_printf(1, "\n");

		ft_printf(1, "l.");
		ft_print_tree(node->left, nb + 1);
		// ft_printf(1, "|%s|\n", node->item);

		print_nb_char(nb, '-');
		ft_printf(1, "\n");

		ft_printf(1, "r.");

		ft_print_tree(node->right, nb + 1);
		ft_printf(1, "\n");
	}
}

void	ft_print_tab_char(char **tab)
{
	int i;

	dprintf(1, "----  tab ----\n");
	i = -1;
	while (tab[++i])
		dprintf(1, "tab[%d] = [%s]\n", i, tab[i]);
	dprintf(1, "tab[%d] = [%s]\n", i, tab[i]);
	dprintf(1, "---------------\n");
}

void	ft_print_tab_dir(t_dir **dir)
{
	int i;

	i = -1;
	while (dir[++i]->dir)
		dprintf(1, "i = %d, file = %s, dir = %d\n", i, dir[i]->file, dir[i]->dir);
	dprintf(1, "i = %d, file = %s, dir = %d\n", i, dir[i]->file, dir[i]->dir);
}