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

int		is_operand(char *str)
{
	if(!ft_strncmp(str, "echo", 5))
		return (4);			// necessaire plutot que '1' ?
	if (!ft_strncmp(str, "cd", 3))
		return (2);
	if (!ft_strncmp(str, "pwd", 4))
		return (3);
	if (!ft_strncmp(str, "export", 7))
		return (6);
	if (!ft_strncmp(str, "unset", 6))
		return (5);
	if (!ft_strncmp(str, "env", 4))
		return (3);
	if (!ft_strncmp(str, "exit", 5))
		return (4);
	return (0);
}

int		is_separator(char c)
{
	return (c == '|' ||
			c == ';');
}

int		skip_spaces(char **str)
{
	int nb_spaces;

	nb_spaces = 0;
	while (**str == ' ')
	{
		(*str)++;
		nb_spaces++;
	}
	return (nb_spaces);
}

void	str_to_separator(char **str)
{
	while (**str && !is_separator(**str))
		(*str)++;
}