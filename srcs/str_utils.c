#include "../includes/minishell.h"

int	ft_strrfind(const char *s, int c)
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

	i = -1;
	while (str[++i] != '\n')
		;
	str[i] = '\0';
	return (str);
}