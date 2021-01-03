/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:15:21 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 15:01:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	*ft_malloc_ptr(int i, int *j, const char *str, char c)
{
	char	*ptr;

	*j = 0;
	while ((str[i + *j] != c) && str[i + *j])
		(*j)++;
	if (!(ptr = malloc(sizeof(char) * (*j + 1))))
		return (NULL);
	*j = 0;
	while (str[i + *j] && (str[i + *j] != c))
	{
		ptr[(*j)] = str[i + *j];
		(*j)++;
	}
	ptr[(*j)] = '\0';
	return (ptr);
}

static int	free_all(char ***str_tab, int i_words)
{
	int	i;

	i = 0;
	while (i < i_words)
		free((*str_tab)[i++]);
	free(*str_tab);
	return (0);
}

static int	sep_str_in_tab(const char *str, char c, char ***str_tab, int *j)
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
			if (!(ptr = ft_malloc_ptr(i, j, str, c)))
				return (free_all(str_tab, i_words));
			new_w = 0;
			i = i + *j;
			(*str_tab)[i_words++] = ptr;
		}
		else if (str[i++] == c)
			new_w = 1;
	}
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**str_tab;
	int		nb_w;
	int		*j;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	j = &i;
	str_tab = 0;
	nb_w = get_nb_words(s, c);
	if (nb_w == 0)
	{
		if (!(str_tab = malloc(sizeof(char*))))
			return (NULL);
		str_tab[0] = 0;
		return (str_tab);
	}
	if (!(str_tab = malloc(sizeof(char*) * (nb_w + 1))))
		return (NULL);
	if (!sep_str_in_tab(s, c, &str_tab, j))
		return (NULL);
	str_tab[nb_w] = 0;
	return (str_tab);
}
