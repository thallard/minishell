/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:42:05 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/12 14:26:03 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_word_len(const char *str, int i, char c)
{
	int j;

	j = 0;
	while ((str[i + j] != '<' || (j > 0 && str[i + j - 1] == '\\'))
			&& (str[i + j] != '>' || (j > 0 && str[i + j - 1] == '\\'))
			&& str[i + j] && str[i + j] != c)
		j++;
	if (j > 0)
		return (-1 * j);
	return (1);
}

static int	get_nb_words(const char *str)
{
	int	i;
	int	nb_w;

	i = 0;
	nb_w = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '<' || !i || str[i - 1] != '>')
				nb_w++;
		}
		i++;
	}
	return (nb_w);
}

static t_dir	*ft_malloc_ptr(t_shell *shell, int *i, const char *str, char c)
{
	t_dir	*ptr;
	int		j;
	int		len;

	if (!(ptr = malloc_lst(shell, sizeof(t_dir))))
		return (NULL);	// a gerer
	j = 0;
	if (str[*i + j] == '<' || str[*i + j] == '>')
		ptr->dir = 1 - (2 * (str[*i + j] == '<'));
	j++;
	if (str[*i + j] == '>' && str[*i + j - 1] == '>' && j++)
		ptr->dir = 2;
	*i += ft_abs(ptr->dir);
	while (str[*i] == c)
		(*i)++;
	len = ft_abs(get_word_len(str, *i, c));
	if (!(ptr->file = malloc_lst(shell, sizeof(char) * (len + 1))))
		return (NULL);
	j = -1;
	while (++j < len)
		(ptr->file)[j] = str[*i + j];
	(ptr->file)[j] = '\0';
	*i = *i + j;
	return (ptr);
}

static int	sep_str_in_tab(t_shell *shell, const char *str, char c, t_dir ***str_tab)
{
	int		i;
	t_dir	*ptr;
	int		i_words;
	int		len;

	i = 0;
	i_words = 0;
	while (str[i])
	{
		len = get_word_len(str, i, c);
		if (str[i] != c && len >= 0)
		{
			if (!(ptr = ft_malloc_ptr(shell, &i, str, c)))
				return (0);
			(*str_tab)[i_words++] = ptr;
		}
		else if (str[i] != c )
				i = i - len;
		else
			i++;
	}
	if (!((*str_tab)[i_words] = malloc_lst(shell, sizeof(t_dir))))
		return (0);
	(*str_tab)[i_words]->file = NULL;
	return (1);
}

t_dir		**ft_split_minishell_dir(char const *s, char c, t_shell *shell)
{
	t_dir	**str_tab;
	int		nb_w;
	int		i;

	i = 0;
	str_tab = 0;
	if (!s)
		nb_w = 0;
	else
		nb_w = get_nb_words(s);		
	if (nb_w == 0)
	{
		if (!(str_tab = malloc_lst(shell, sizeof(t_dir*))))
			return (NULL);
		if (!(str_tab[0] = malloc_lst(shell, sizeof(t_dir))))	// sans l'etoile
			return (NULL);	// a gerer
		(str_tab[0])->file = NULL;	// OK ?
		return (str_tab);
	}
	if (!(str_tab = malloc_lst(shell, sizeof(t_dir*) * (nb_w + 1))))
		return (NULL);
	if (!sep_str_in_tab(shell, s, c, &str_tab))
		return (NULL);
	i = -1;
	return (str_tab);
}
