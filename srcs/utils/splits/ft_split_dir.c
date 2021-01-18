/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:33 by thallard          #+#    #+#             */
/*   Updated: 2021/01/18 14:27:10 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char	*ft_exit_splt(char *str)	// deja definie ailleurs, non ?
// {
// 	ft_printf(1, "%s", str);
// 	return (NULL);
// }

static int	ft_skip_quotes(t_shell *shell, char *str_bis)
{
	int		k;
	char	c;

	k = 1;
	c = str_bis[0];
	while (str_bis[k] && str_bis[k] != c)
		k++;
	if (!str_bis[k])
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	return (k);
}

int	is_redirection(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (i > 0 && str[i] == '>' && str[i - 1] == '2' &&
			(i == 1 || str[i - 2] == ' '))
		return (3);
	else if (str[i] == '>')
		return (1);
	else if (str[i] == '<')
		return (-1);
	return (0);
}

char		*ft_create_word_double_dir(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))	// 1000
		return (NULL);	// a gerer
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
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
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
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))	// 1000
		ft_exit_failure(shell, F_MALLOC, NULL);
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
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	*iterator += i;
	return (word);
}

t_dir	**ft_split_redirection(t_shell *shell, char *str)
{
	t_dir	**tab;
	int		i;
	int		j;
	int		redirection;
	t_dir	*tab_temp;

	if (!(tab = malloc_lst(shell, sizeof(t_dir *) * 40)))
		return (NULL);
	i = -1;
	j = -1;
	while (ft_strlen(str) >= ++i && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_skip_quotes(shell, str + i);
		else if ((redirection = is_redirection(str, i)) != 0 &&
			!(tab_temp = ft_add_redirection(shell, str, &i, &j)))
			tab[j] = tab_temp;
		shell->split->d_quotes = 0;
		shell->split->s_quotes = 0;	// toujours remettre a zero ou juste si redirection ?
	}
	if (!(tab[++j] = malloc_lst(shell, sizeof(t_dir))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	(tab[j])->file = NULL;
	return (tab);
}


/*
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
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_skip_quotes(shell, str + i);
		else if ((redirection = is_redirection(str, i))!= 0)
		{
			ft_add_redirection(shell, str, &i, &j);
			// if (redirection == 3)
			// 	i += ft_add_dir_error(shell, str + i);
			// else
			// {
			// 	if (redirection == 2)
			// 		i++;
			// 	if (!(tab[++j] = malloc_lst(shell, sizeof(t_dir))))
			// 		return (NULL);		// a gerer
			// 	while (str[++i] == ' ')
			// 		;
			// 	if (str[i] != '\'' && str[i] != '\"')
			// 		tab[j]->file = ft_create_word_dir(shell, shell->split, &str[i], &i);
			// 	else if (str[i] == '\"' && !shell->split->d_quotes++)
			// 		tab[j]->file = ft_create_word_double_dir(shell, &str[++i], &i);
			// 	else
			// 		tab[j]->file = ft_create_word_simple_dir(shell, &str[++i], &i);	// fonction a ajouter
			// 	tab[j]->dir = redirection;
			// }
			shell->split->d_quotes = 0;
			shell->split->s_quotes = 0;
		}
	}
	if (!(tab[++j] = malloc_lst(shell, sizeof(t_dir))))
		return (NULL);		// a gerer
	(tab[j])->file = NULL;
	return (tab);
}
*/