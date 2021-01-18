/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:30:29 by thallard          #+#    #+#             */
/*   Updated: 2021/01/18 14:03:06 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_tab_args(t_args *tab)
{
	int i = -1;
	while (tab->args[++i])
		ft_printf(1, "args[%d] = %s | var[%d] = %d\n", i, tab->args[i], i, tab->var[i][0]);
}

char	*create_simple(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	// ft_printf(1,"entree simple = %s\n", str);
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i])
		if (str[i] == '\'' && ++shell->split->s_quotes >= 2)
			break ;
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (shell->split->s_quotes % 2 == 1)
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i + 1;
	return (word);
}


char	*create_argd(t_shell *shell, char *str, int *iterator, int *env)
{
	char	*word;
	int		i;
	int		j;
	int		k;

	k = -1;
	j = -1;
	i = -1;
	// ft_printf(1,"entree double = %s\n", str);
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i])
		if (str[i] == '\"' && shell->split->d_quotes++)
			break ;
		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
			word[++j] = str[++i];
		else if (str[i] == '$' && str[i + 1])
		{
			env[++k] = ft_fill_split_env(&str[i]);
			word[++j] = str[i];
		}
		else
			word[++j] = str[i];
	word[++j] = '\0';
	*iterator += i;
	if (str[i] != '\"')
		ft_exit_split(shell, "Error : need a double quote to finish the line.\n");
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	return (word);
}

static char		*create_args(t_shell *shell, char *str, int *iterator, int *env)
{
	char	*word;
	int		i;
	int		j;
	int		k;

	k = -1;
	j = -1;
	i = -1;
	// ft_printf(1,"entree arg = %s\n", str);
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	
	while (str[++i])
		if (str[i] == ' ' && (shell->split->d_quotes == 0 && shell->split->s_quotes == 0) && i != 0)
			break ;
		else if (str[i] == '\'' && ++shell->split->s_quotes)
			continue ;
		else if (str[i] == '\"')
			 shell->split->d_quotes++;
		else if (str[i] == '$' && str[i + 1])
		{
			if (shell->split->s_quotes >= 1 && shell->split->d_quotes % 2 == 0)
				env[++k] = -1;
			else
				env[++k] = ft_fill_split_env(&str[i]);
			word[++j] = str[i];
		}
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (k == -1)
		env[0] = -1;
	else
		env[++k] = -1;
	if (ft_strlen(word) == 0)
		word[0] = '\0';
	if (shell->split->d_quotes % 2 != 0)
		ft_exit_split(shell, "Error : need a quote to finish the line1.\n");
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
		shell->split->d_quotes = 0;
		shell->split->s_quotes = 0;
		if (str[i] == ' ')
			continue ;
		else if ((str[i] == '>' || str[i] == '<') && i++ > -10)
		{
			if (str[i] == '>')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
		}
		else if (str[i] == '\"' && !shell->split->d_quotes++)
		{
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, str));
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 1 && i != ft_strlen(str) - 1)
			{
				str[i] = ' ';
				args->args[j] = create_argd(shell, &str[i], &i, args->var[j]);
			}
			else
			{
				args->args[j] = create_argd(shell, &str[++i], &i, args->var[j]);
			}
		}
		else if (str[i] == '\'' && !shell->split->s_quotes++)
		{
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, str));
			args->var[j][0] = -1;
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 1 && i != ft_strlen(str) - 1)
			{
				str[i] = ' ';
				args->args[j] = create_simple(shell, &str[i], &i);
			}
			else
			{
				args->args[j] = create_simple(shell, &str[++i], &i);
			}
		}
		else
		{
			
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, str));
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 1 && i != ft_strlen(str) - 1)
			{
				str[i - 1] = ' ';
				args->args[j] = create_args(shell, &str[--i], &i, args->var[j]);
			}
			else
				args->args[j] = create_args(shell, &str[i], &i, args->var[j]);
		}
	}
	args->args[++j] = NULL;
	// args->var[j] = malloc_lst(shell, sizeof(int *) * 1);
	args->var[j] = NULL;
	// print_tab_args(args);
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