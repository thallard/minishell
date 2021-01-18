/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:56:52 by thallard          #+#    #+#             */
/*   Updated: 2021/01/18 14:03:49 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/minishell.h"


// char	*ft_create_word(t_shell *shell, t_split *s, char *str, int *iterator)
// {
// 	char	*word;
// 	int		i;
// 	int		j;
// 	char	*env;

// 	j = -1;
// 	i = -1;
// 	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
// 		return (NULL);
// 	while (str[++i])
// 		if (str[i] == ' ' && (s->d_quotes == 0 && s->s_quotes == 0))
// 			break ;
// 		else if (str[i] == '\'' && s->s_quotes++ >= 0)
// 			word[++j] = str[i];
// 		else if (str[i] == '\"')
// 			s->d_quotes++;
// 		else if (str[i] == '$' && str[i + 1])
// 			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
// 				continue ;
// 			else
// 				while (*env)
// 					word[++j] = *env++;
// 		else
// 			word[++j] = str[i];
// 	word[++j] = '\0';
// 	if (s->d_quotes % 2 != 0 || s->s_quotes % 2 != 0)
// 		return (ft_exit_split("Error : need a quote to finish the line.\n"));
// 	*iterator += i;
// 	return (word);
// }

// char	*ft_create_word_simple(t_shell *shell, char *str, int *iterator)
// {
// 	char	*word;
// 	int		i;
// 	int		j;

// 	j = -1;
// 	i = -1;
// 	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
// 		return (NULL);
// 	while (str[++i])
// 		if (str[i] == '\'' && shell->split->s_quotes++)
// 			break ;
// 		else
// 			word[++j] = str[i];
// 	word[++j] = '\0';
// 	if (shell->split->s_quotes == 1)
// 		return (ft_exit_split("Error : need a quote to finish the line.\n"));
// 	*iterator += i + 1;
// 	return (word);
// }

// char	*ft_create_word_double(t_shell *shell, char *str, int *iterator)
// {
// 	char	*word;
// 	int		i;
// 	int		j;
// 	char	*env;

// 	j = -1;
// 	i = -1;
// 	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
// 		return (NULL);
// 	while (str[++i] && str[i] != ' ')
// 		if (str[i] == '\"')
// 			continue ;
// 		else if (str[i] == '$' && str[i + 1])
// 			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
// 				continue ;
// 			else
// 				while (*env)
// 					word[++j] = *env++;
// 		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
// 			word[++j] = str[++i];
// 		else
// 			word[++j] = str[i];
// 	word[++j] = '\0';
// 	if (str[i] != '\"')
// 		return (ft_exit_split("Error : need a double quote to finish the line.\n"));
// 	*iterator += i + 1;
// 	return (word);
// }

// char	**ft_split_quotes(t_shell *shell, t_split *s, char *str)
// {
// 	int		i;
// 	int		j;
// 	char	**tab;

// 	if (!(tab = malloc_lst(shell, sizeof(char *) * 100)))
// 		return (NULL);
// 	i = 0;
// 	j = -1;
// 	if (!str)
// 		return (tab);
// 	// dprintf(1, "str en entree = %s\n", str);
// 	while (ft_strlen(str) >= i && str[i])
// 	{
// 		if (str[i] == '\"' && !s->d_quotes++)
// 			tab[++j] = ft_create_word_double(shell, &str[++i], &i);
// 		else if (str[i] == '\'' && !s->s_quotes++)
// 			tab[++j] = ft_create_word_simple(shell, &str[++i], &i);
// 		else if (str[i] == ' ')
// 			i++;
// 		else
// 			tab[++j] = ft_create_word(shell, shell->split, &str[i], &i);
// 		if (!tab[j])
// 		{
// 			return (NULL);
// 		}
// 		s->d_quotes = 0;
// 		s->s_quotes = 0;
// 	}
// 	tab[++j] = NULL;
// 	return (tab);
// }