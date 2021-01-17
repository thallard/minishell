#include "../../../includes/minishell.h"

// void	print_tab_args(t_args *tab)
// {
// 	int i = -1;
// 	while (tab->args[++i])
// 		ft_printf(1, "args[%d] = %s | var[%d] = %d\n", i, tab->args[i], i, tab->var[i]);
// }

char	*create_simple(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i])
		if (str[i] == '\'' && ++shell->split->s_quotes == 2)
			break ;
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (shell->split->s_quotes == 1)
		return (ft_exit_split("Error : need a quote to finish the line.\n"));
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i + 1;
	return (word);
}


char	*create_argd(t_shell *shell, t_split *s, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i] && str[i] != '<' && str[i] != '>')
		if (str[i] == '\"' && ++s->d_quotes == 2 && (word[++j] = str[i]))
			break ;
		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
			word[++j] = str[++i];
		else if (str[i] == '$' && str[i + 1] && s->env++ >= 0)
			word[++j] = str[i];
		else
			word[++j] = str[i];
	word[++j] = '\0';
	*iterator += i + 1;
	if (str[i] != '\"')
		return (ft_exit_split("Error : need a double quote to finish the line.\n"));
	s->d_quotes = 0;
	s->s_quotes = 0;
	return (word);
}

static char		*create_args(t_shell *shell, t_split *s, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))	// Pourquoi + 1000 ?
		return (NULL);
	while (str[++i] && str[i] != '>' && str[i] != '<')
		if (str[i] == ' ' && (s->d_quotes % 2 == 0 && s->s_quotes % 2 == 0) && i != 0)
			break ;
		else if (str[i] == '\'')
			word[++j] = str[i];
		else if (str[i] == '\"' && s->d_quotes++ >=0)
			word[++j] = str[i];
		else if (str[i] == '$' && str[i + 1] && s->env++ >= 0)
			word[++j] = str[i];
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (ft_strlen(word) == 0)
		word[0] = '\0';
	if (s->d_quotes % 2 != 0 || s->s_quotes % 2 != 0)
		return (ft_exit_split("Error : need a quote to finish the line2.\n"));
	if (str[i] == '>' || str[i] == '<')
		i--;
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i;
	return (word);
}

t_args		*ft_split_args(t_shell *shell, char *str)
{
	int		i;
	int		j;
	t_args	*args;

	j = -1;
	i = -1;
	if (!(args = malloc_lst(shell, sizeof(t_args))))
		return (NULL);
	if (!(args->args = malloc_lst(shell, sizeof(char *) * 10)))
		return (NULL);
	if (!(args->var = malloc_lst(shell, sizeof(int *) * 10)))
		return (NULL);
	// ft_printf(1,"entree = %s\n", str);
	while (ft_strlen(str) >= ++i && str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '\"')
			args->args[++j] = create_argd(shell, shell->split, &str[i], &i);
		else if (str[i] == '\'')
			args->args[++j] = create_simple(shell, &str[i], &i);
		else
			args->args[++j] = create_args(shell, shell->split, &str[i], &i);
		args->var[j] = 0;
		// if (s->split->env)	// ou split et env sont-elles est-elle initialisees ?
		// 	args->var[j] = 1;
		// s->split->env =
		if (shell->split->env)	// ou split et env sont-elles est-elle initialisees ?
			args->var[j] = 1;
		shell->split->env = 0;
	}
	args->args[++j] = NULL;
	args->var[j] = -1;
	// print_tab_args(node->arg);
	return (args);
}


// t_args		*ft_split_args(t_shell *s, char *str, t_tree *node)
// {
// 	int		i;
// 	int		j;
// 	t_args	*args;

// 	j = -1;
// 	i = -1;
// 	if (!(node->args = malloc_lst(s, sizeof(t_args))))
// 		return (NULL);
// 	if (!(node->args->args = malloc_lst(s, sizeof(char *) * 10)))
// 		return (NULL);
// 	if (!(node->args->var = malloc_lst(s, sizeof(int *) * 10)))
// 		return (NULL);
// 	// ft_printf(1,"entree = %s\n", str);
// 	while (ft_strlen(str) >= ++i && str[i])
// 	{
// 		if (str[i] == ' ')
// 			i++;
// 		else if (str[i] == '\"')
// 			node->args->args[++j] = create_argd(s, s->split, &str[i], &i);
// 		else if (str[i] == '\'')
// 			node->args->args[++j] = create_simple(s, &str[i], &i);
// 		else
// 			node->args->args[++j] = create_args(s, s->split, &str[i], &i);
// 		node->args->var[j] = 0;
// 		if (s->split->env)
// 			node->args->var[j] = 1;
// 		s->split->env = 0;
// 	}
// 	node->args->args[++j] = NULL;
// 	node->args->var[j] = -1;
// 	// print_tab_args(node->arg);
// 	return (node->args);
// }