#include "../../includes/minishell.h"

int	find_exec(t_shell *shell, t_tree *node)
{
	ft_printf("find_exec -> %s / %s\n", node->item, node->left->item);
	return (1);
}

int	ft_exec(t_shell *shell, t_tree *node)
{
	if(!ft_strncmp(node->item, "echo", 5))
		return (ft_echo(shell, node));
	if (!ft_strncmp(node->item, "cd", 3))
		return (ft_cd(shell, node));
	if (!ft_strncmp(node->item, "pwd", 4))
		return (ft_pwd(shell));
	// if (!ft_strncmp(node->item, "export", 7))
	// 	return (ft_export(shell, node));
	// if (!ft_strncmp(node->item, "unset", 6))
	// 	return (ft_unset(shell, node));
	// if (!ft_strncmp(node->item, "env", 4))
	// 	return (ft_env(shell, node));
	// if (!ft_strncmp(node->item, "exit", 5))
	// 	return (ft_exit(shell, node));
	return (find_exec(shell, node));
}

int	read_tree(t_shell *shell)
{
	int		is_end;
	t_tree	*t_current;
	int		res;

	t_current = shell->root;
	is_end = (t_current->right != NULL);
	while (is_end)
	{
		t_current = t_current->right;
		if (!strncmp(t_current->item, ";", 2))	//	a voir pour |
		{
			res = ft_exec(shell, t_current->left);	// a traiter
			is_end = (t_current->right != NULL);
		}
		else
		{
			res = ft_exec(shell, t_current);
			is_end = 0;
		}
	}
	return (SUCCESS);
}
