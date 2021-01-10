/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:56:52 by thallard          #+#    #+#             */
/*   Updated: 2021/01/10 16:05:02 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

	// char	*word;
	// int		i;
	// int		j;
	// char	*env;
	// int		k;

	// k = -1;
	// i = -1;
	// j = -1;
	// dprintf(1, "str en entree = %s\n", str);
	// if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
	// 	return (NULL);
	// while (str[++i] && (str[i] != ' ' && shell->split.d_quotes == 0) && (str[i] != '\"' && shell->split.d_quotes == 0))
	// {
	// 	if (str[i] == '\"')
	// 		shell->split.d_quotes++;
	// 	if (str[i] == '\'')
	// 		shell->split.s_quotes++;
	// 	if (ft_strncmp(&str[i], "\\\"", 2) == 0)
	// 		word[++j] = str[++i];
	// 	else if (str[i] == '$' && str[i + 1] && ((shell->split.d_quotes >= 1 && shell->split.s_quotes >= 1) || (shell->split.s_quotes == 0)))
	// 	{
	// 		dprintf(1, "debug de d quote s= %d\n", shell->split.s_quotes);
	// 		if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
	// 			continue ;
	// 			k = -1;
	// 		while (env[++k])
	// 			word[++j] = env[k];
	// 	}
	// 	else
	// 	{

	// 		word[++j] = str[i];
	// 	} 
		
		
	// }
	// word[++j] = '\0';
	// *iterator += i;
	// dprintf(1, "debug word = |%s|\n", word);
	// if (shell->split.d_quotes == 1 && str[i] != '\"')
	// 	shell->split.d_quotes = 0;
	// shell->split.s_quotes = 0;
// 	return (word);
char	*ft_create_word(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	char	*env;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == ' ' && shell->split->d_quotes == 0)
			break ;
		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
			word[++j] = str[++i];
		else if (ft_strncmp(&str[i], "\\\'", 2) == 0 && shell->split->s_quotes == 0 && shell->split->d_quotes == 0)
			word[++j] = str[++i];
		else if (str[i] == '\"' && shell->split->d_quotes == 0)
			continue ;
		else if (str[i] == '\"' && shell->split->d_quotes >= 1)
			break ;
		else if (str[i] == '\'' && shell->split->d_quotes == 0 && ++shell->split->s_quotes >= 1)
			continue ;
		else if (str[i] == '$' && str[i + 1] && shell->split->s_quotes == 0)
		{
			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
				continue ;
			while (*env)
				word[++j] = *env++;
		}
		else
			word[++j] = str[i];
	}
	word[++j] = '\0';
	shell->split->d_quotes = 0;
		shell->split->s_quotes = 0;
	if (str[i] == '\"')
		i++;
	*iterator += i;
	return (word);


}

char	**ft_split_quotes(t_shell *shell, t_split *s, char *str)
{
	int		i;
	int		j;
	char	**tab;

	tab = malloc(sizeof(char *) * 10);
	i = 0;
	j = -1;
	// dprintf(1, "str en entree = %s\n", str);
	while (ft_strlen(str) >= i && str[i])
	{
		if (str[i] == '\"')
		{
			s->d_quotes++;
			tab[++j] = ft_create_word(shell, &str[++i], &i);
		}
		else if (str[i] == ' ' && shell->split->d_quotes == 0)
			i++;
		else if (str[i] == '\'' && shell->split->s_quotes >= 1)
			break ;
		else
			tab[++j] = ft_create_word(shell, &str[i], &i);
			// ft_printf(1, "word = %s\n", tab[j]);
			// i += ft_strlen(tab[j]);
	
			
	}
	tab[++j] = NULL;
	return (tab);
}