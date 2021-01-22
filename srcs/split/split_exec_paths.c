/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exec_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:15:21 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 12:58:58 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_word_len(const char *str, int i, char c)
{
	int j;
	int	indice;

	j = 0;
	indice = 1;
	if (str[i + j] == '<' || str[i + j] == '>')
	{
		indice = -1;
		if (str[i + j] == '<' && str[i + j + 1] == '<')
			j++;
		j++;
	}
	while (indice == -1 && str[i + j] == c && str[i + j])
		j++;
	while (str[i + j] != c && str[i + j]
			&& (str[i + j] != '<' || str[i + j - 1] == '\\')
			&& (str[i + j] != '>' || str[i + j - 1] == '\\'))
		j++;
	return (indice * j);
}

static int	get_nb_words(const char *str, char c)
{
	int	i;
	int	nb_w;

	i = 1;
	nb_w = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i - 1] != c)
				nb_w++;
		}
		i++;
	}
	if (str[i - 1] != c)
		nb_w++;
	return (nb_w);
}

static char	*ft_malloc_ptr(t_shell *shell, int *i, const char *str, char c)
{
	char	*ptr;
	int		j;
	int		len;

	len = get_word_len(str, *i, c);
	if (!(ptr = malloc_lst(shell, sizeof(char) * (len + 1))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	j = -1;
	while (++j < len)
		ptr[j] = str[*i + j];
	ptr[j] = '\0';
	*i = *i + j;
	return (ptr);
}

static int	sep_str_in_tab(t_shell *shell, const char *str, char c,
							char ***str_tab)
{
	int		i;
	char	*ptr;
	int		new_w;
	int		i_words;

	new_w = 1;
	i = 0;
	i_words = 0;
	while (str[i])
	{
		if ((str[i] != c) && new_w)
		{
			if (get_word_len(str, i, c) >= 0)
			{
				ptr = ft_malloc_ptr(shell, &i, str, c);
				new_w = 0;
				(*str_tab)[i_words++] = ptr;
			}
			else
				i = i - get_word_len(str, i, c);
		}
		else if (str[i++] == c)
			new_w = 1;
	}
	return (i_words);
}

char		**ft_split_exec_paths(char const *s, char c, t_shell *shell)
{
	char	**str_tab;
	int		nb_w;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str_tab = 0;
	nb_w = get_nb_words(s, c);
	if (nb_w == 0)
	{
		if (!(str_tab = malloc_lst(shell, sizeof(char*))))
			ft_exit_failure(shell, F_MALLOC, NULL);
		str_tab[0] = 0;
		return (str_tab);
	}
	if (!(str_tab = malloc_lst(shell, sizeof(char*) * (nb_w + 1))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	nb_w = sep_str_in_tab(shell, s, c, &str_tab);
	str_tab[nb_w] = NULL;
	return (str_tab);
}
