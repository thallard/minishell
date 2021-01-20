/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:30:29 by thallard          #+#    #+#             */
/*   Updated: 2021/01/19 17:18:33 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	print_tab_args(t_args *tab)
// {
// 	int i = -1;
// 	int	j = -1;
// 	dprintf(1, "debug entree print tab = %s\n", tab->args[0]);
// 	while (tab->args[++i])
// 	{
// 		j = -1;
// 		dprintf(1, "valeur de tab[%d] = [%s]\n", i, tab->args[i]);
// 			while (tab->var[i][++j] > 0)
// 		dprintf(1, "args[%d] = %s | var[%d] = %d\n", i, tab->args[i], i, tab->var[i][j]);
// 	}
	
// }

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
		ft_exit_split(shell, "Error : need a quote to finish the line11.\n");
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i;
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
			// dprintf(1,"entree simpeqweqweqwle = %d\n", env[k]);
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
	int		temp;

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
			{
				temp = j;
				if (ft_get_env_value(shell, str + i, &j, i))
				{
					env[++k] = ft_fill_split_env(&str[i]);
					j = temp;
					i += temp;
				}
				else
				{
					i += temp;
					j = temp;
				}
			}
				
				
				
		
			// dprintf(1,"valeur de env sur le simple word = %d\n", env[k]);
			word[++j] = str[i];
		}
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (k == -1)
		env[0] = -1;
	else
		env[++k] = -1;
	// dprintf(1, "debug word = [%s]\n", word);
	if (ft_strlen(word) <= 2)
		word[0] = '\0';
	// dprintf(1, "srotie de debug du create word simple = [%s]\n", word);
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
	char	*temp;

	if (!(temp = ft_strdup(str)) || !(add_lst_to_free(shell, temp)))
		return (NULL);
	j = -1;
	i = -1;
	if (!(args = malloc_lst(shell, sizeof(t_args))))
		return (NULL);
	if (!(args->args = malloc_lst(shell, sizeof(char *) * 10)))
		return (NULL);
	if (!(args->var = malloc_lst(shell, sizeof(int *) * 10)))
		return (NULL);
	// ft_printf(1,"entree = %s\n", str);
	while (ft_strlen(temp) >= ++i && temp[i])
	{
		if (temp[i] == ' ')
			continue ;
		else if ((temp[i] == '>' || temp[i] == '<') && i++ > -10)
		{
			if (temp[i] == '>')
				i++;
			while (temp[i] && temp[i] == ' ')
				i++;
			while (temp[i] && temp[i] != ' ' && temp[i] != '>' && temp[i] != '<')
				i++;
		}
		else if (temp[i] == '\"' && !shell->split->d_quotes++)
		{
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, temp));
			if (i - 1 >= 0 && temp[i - 1] == ' ' && j != 1 && i != ft_strlen(temp) - 1)
			{
			// dprintf(1, "jmets un espace cc\n");

				temp[i] = ' ';
				args->args[j] = create_argd(shell, &temp[i], &i, args->var[j]);
			}
			else
			{
				args->args[j] = create_argd(shell, &temp[++i], &i, args->var[j]);
			}
			// dprintf(1, "j vaut = %d et %d\n", args->var[j][0], j);
		}
		else if (temp[i] == '\'' && !shell->split->s_quotes++)
		{
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, temp));
			args->var[j][0] = 0;
			args->var[j][1] = -1;
			// dprintf(1, "j vaut = %d et %d\n", args->var[j][0], j);
			if (i - 1 >= 0 && temp[i - 1] == ' ' && j != 1 && i != ft_strlen(temp) - 1)
			{
				temp[i] = ' ';
				args->args[j] = create_simple(shell, &temp[i], &i);
			
			}
			else
			{
				args->args[j] = create_simple(shell, &temp[++i], &i);
	
			}
				// dprintf(1, "sortie de ismple quote1 = [%s]\n", &temp[i]);
		}
		else if (i <= ft_strlen(temp) - 1)
		{
			// dprintf(1, "sortie de ismple quote1 = [%s]\n", &temp[i]);
			args->var[++j] = malloc_lst(shell, sizeof(int *)
			* ft_get_nb_env(shell, temp));
			if (i - 1 >= 0 && temp[i - 1] == ' ' && j != 1 && i <= ft_strlen(temp) - 1)
			{
				temp[i - 1] = ' ';
				args->args[j] = create_args(shell, &temp[--i], &i, args->var[j]);
				
			}
			else
				args->args[j] = create_args(shell, &temp[i], &i, args->var[j]);
			// dprintf(1, "j vaut = %d et %d\n", args->var[j][0], j);
			// dprintf(1, "jmets un espace cc\n");
		}
			shell->split->d_quotes = 0;
		shell->split->s_quotes = 0;
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