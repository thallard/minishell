/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:52:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/12 19:19:52 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_create_word_arg(t_shell *shell, t_split *s, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	//dprintf(1, "dbeug entree de create word arg arg = %s\n", str);
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
		return (ft_exit_split("Error : need a quote to finish the line.\n"));
	*iterator += i;
	return (word);
}

char	**ft_split_args_quotes(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	**res;

	//dprintf(1, "debug en entree str = [%s]\n", str);
	if (!(res = malloc_lst(shell, sizeof(char *) * 40)))
		return (NULL);
	i = 0;
	j = -1;
	while (ft_strlen(str) >= i && str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '\"' && !shell->split->d_quotes++)
			;
		else
			res[++j] = ft_create_word_arg(shell, shell->split, &str[i++], &i);
	}
	res[++j] = NULL;
	//ft_print_tab_char(res);
	return (res);
}