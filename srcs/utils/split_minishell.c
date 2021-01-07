/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:15:21 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 12:23:41 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	j = 0;
	while ((str[*i + j] != c) && str[*i + j])
		(j)++;
	if (!(ptr = malloc_lst(shell, sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (str[*i + j] && (str[*i + j] != c))
	{
		ptr[(j)] = str[*i + j];
		(j)++;
	}
	ptr[(j)] = '\0';
	*i = *i + j;
	return (ptr);
}

static int	sep_str_in_tab(t_shell *shell, const char *str, char c, char ***str_tab)
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
			if (!(ptr = ft_malloc_ptr(shell, &i, str, c)))
				return (0);
			new_w = 0;
			(*str_tab)[i_words++] = ptr;
		}
		else if (str[i++] == c)
			new_w = 1;
	}
	return (1);
}

char		**ft_split_minishell(char const *s, char c, t_shell *shell)
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
			return (NULL);
		str_tab[0] = 0;
		return (str_tab);
	}
	if (!(str_tab = malloc_lst(shell, sizeof(char*) * (nb_w + 1))))
		return (NULL);
	if (!sep_str_in_tab(shell, s, c, &str_tab))
		return (NULL);
	str_tab[nb_w] = 0;
	return (str_tab);
}
