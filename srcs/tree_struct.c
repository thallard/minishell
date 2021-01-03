#include "../includes/minishell.h"

/*
**	Separateurs a gerer :
**		;
**		|
**		" " et ' '
**
**
**
*/

t_tree	*tree_create_node(void *item)
{
	t_tree	*node;

	if (!(node = malloc(sizeof(t_tree*))))
		return (NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int		is_operand(char *str)
{
	if(!ft_strncmp(str, "echo", 4))
		return (4);
	if (!ft_strncmp(str, "cd", 2))
		return (2);
	if (!ft_strncmp(str, "pwd", 3))
		return (3);
	if (!ft_strncmp(str, "export", 6))
		return (6);
	if (!ft_strncmp(str, "unset", 5))
		return (5);
	if (!ft_strncmp(str, "env", 3))
		return (3);
	if (!ft_strncmp(str, "exit", 4))
		return (4);
	return (0);
}

int		is_separator(char c)
{
	return (c == '|' ||
			c == ';');
}

char *strdup_and_inc_input(char **input, int len)
{
	char *op;
	int i;

	if (!(op = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		op[i++] = *((*input)++);
	op[i] = 0;
	return (op);
}

t_tree	*add_left_node(t_tree *node, char **input, int len)
{
	t_tree	*l_node;
	char	*op;

	op = strdup_and_inc_input(input, len);
	l_node = tree_create_node(op);
	return (l_node);
}


t_tree	*read_input(t_tree *t_root, char *input) // faut il trim les espaces ?
{
	int		len_op;
	t_tree	*node;

	if(!(*input))
		return (0);
	if(!(len_op = is_operand(input)))
		return (-1);
	node = add_left_node(t_root, &input, len_op);
	return (1);
}

t_tree	*create_main_tree(t_shell *shell, char *input)
{
	t_tree	*t_root;
	int		is_end;

	t_root = tree_create_node(NULL);
	is_end = 1;
	while (is_end)
		is_end = read_input(t_root, &input);

}