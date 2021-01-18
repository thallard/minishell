/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:07:51 by thallard          #+#    #+#             */
/*   Updated: 2021/01/18 14:35:52 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		ft_add_dir_error(t_shell *shell, char *str_bis)
{
	int j;

	j = 0;
	if (str_bis[1] == '\"')
		shell->dir_err = ft_create_word_double_dir(shell, str_bis + 1, &j);
	if (str_bis[1] == '\'')
		shell->dir_err = ft_create_word_simple_dir(shell, str_bis + 1, &j);
	else
		shell->dir_err = ft_create_word_dir(shell, shell->split, str_bis + 1, &j);
	return (j);
}

t_dir	*ft_add_redirection(t_shell *shell, char *str, int *i, int *j)
{
	int redirection;
	t_dir	*tab_j;

	tab_j = NULL;
	redirection = is_redirection(str, *i);
	if (redirection == 3)
		i += ft_add_dir_error(shell, str + *i);
	else
	{
		if (redirection == 2)
			i++;
		if (!(tab_j = malloc_lst(shell, sizeof(t_dir))) && (++(*j) < 0))
			ft_exit_failure(shell, F_MALLOC, NULL);		
		while (str[++(*i)] == ' ')
			;
		if (str[*i] != '\'' && str[*i] != '\"')
			tab_j->file = ft_create_word_dir(shell, shell->split, &str[*i], i);
		else if (str[*i] == '\"' && !shell->split->d_quotes++)
			tab_j->file = ft_create_word_double_dir(shell, &str[++(*i)], i);
		else
			tab_j->file = ft_create_word_simple_dir(shell, &str[++(*i)], i);	// fonction a ajouter
		tab_j->dir = redirection;
	}
	return (tab_j);
}

char	*ft_create_word_simple_dir(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char *) * ft_strlen(str) + 1000)))
		return (NULL);
	while (str[++i] && str[i] != '>' && str[i] != '<')
		if (str[i] == '\'')
			break ;
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (str[i] != '\'')
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i + 1;
	return (word);
}