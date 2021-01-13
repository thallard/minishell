/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:33 by thallard          #+#    #+#             */
/*   Updated: 2021/01/13 08:37:24 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_exit_splt(char *str)
{
	ft_printf(1, "%s", str);
	return (NULL);
}

int		is_redirection(char *str)
{
	if (str[0] == '>')
		return (1);
	else if (ft_strncmp(&str[0], ">>", 2) == 0)
		return (2);
	else if (str[0] == '<')
		return (-1);
	return (0);
}

char	*ft_create_word_double_dir(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		if (str[i] == '\"')
			break ;
		else if (str[i] == '$' && str[i + 1])
			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
				continue ;
			else
				while (*env)
					word[++j] = *env++;
		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
			word[++j] = str[++i];
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (str[i] != '\"')
		return (ft_exit_splt("Error : need a double quote to finish the line.\n"));
	*iterator += i + 1;
	return (word);
}

char	*ft_create_word_dir(t_shell *shell, t_split *s, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	// dprintf(1, "dbeug entree de create word = %s\n", str);
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i] && str[i] != '>' && str[i] != '<')
		if (str[i] == ' ' && (s->d_quotes == 0 && s->s_quotes == 0))
			break ;
		else if (str[i] == '\'')
			word[++j] = str[i];
		else if (str[i] == '\"')
			s->d_quotes++;
		else if (str[i] == '$' && str[i + 1])
			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
				continue ;
			else
				while (*env)
					word[++j] = *env++;
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (s->d_quotes % 2 != 0 || s->s_quotes % 2 != 0)
		return (ft_exit_splt("Error : need a quote to finish the line.\n"));
	*iterator += i;
	return (word);
}

t_dir	**ft_split_redirection(t_shell *shell, char *str)
{
	t_dir **tab;
	int		i;
	int		j;
	int		redirection;

	if (!(tab = malloc_lst(shell, sizeof(t_dir *) * 40)))
		return (NULL);
	i = -1;
	j = -1;
	while (ft_strlen(str) >= ++i && str[i])
		if ((redirection = is_redirection(&str[i]) != 0))
		{
			if (!(tab[++j] = malloc_lst(shell, sizeof(t_dir))))
				return (NULL);
			while (str[++i] == ' ')
				;
			if (str[i] != '\'' && str[i] != '\"')
				tab[j]->file = ft_create_word_dir(shell, shell->split, &str[i], &i);
			else if (str[i] == '\"' && !shell->split->d_quotes++)
				tab[j]->file = ft_create_word_double_dir(shell, &str[++i], &i);
			tab[j]->dir = redirection;
			shell->split->d_quotes = 0;
			shell->split->s_quotes = 0;
		}
	if (!(tab[++j] = malloc_lst(shell, sizeof(t_dir))))
				return (NULL);
	(tab[j])->file = NULL;
	return (tab);
}