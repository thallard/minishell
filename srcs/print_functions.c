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
		ft_printf("0\n");
	}
	else
	{
		print_nb_char(nb, ' ');
		ft_printf("|%s|\n", node->item);

		print_nb_char(nb, '-');
		ft_printf("\n");

		ft_printf("l.");
		ft_print_tree(node->left, nb + 1);
		// ft_printf("|%s|\n", node->item);

		print_nb_char(nb, '-');
		ft_printf("\n");

		ft_printf("r.");

		ft_print_tree(node->right, nb + 1);
		ft_printf("\n");
	}
}