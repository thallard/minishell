/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:46:32 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:26:42 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		ft_strrfind(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char*)s;
	if (!ptr)
		return (-1);
	i = 0;
	while (ptr[i])
		i++;
	while (i >= 0 && ptr[i] != (char)c)
		i--;
	return (i);
}

char	*ft_remove_eol(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
	return (str);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strncmp_lower(const char *s1, const char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2, int f_s1, int f_s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	while (++i < l1)
		str[i] = s1[i];
	while (++j < l2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (f_s2)
		free(s2);
	if (f_s1)
		free(s1);
	return (str);
}
