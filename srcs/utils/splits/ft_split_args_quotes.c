/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:52:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/15 14:12:42 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_create_word_double_arg(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i] && str[i] != '<' && str[i] != '>')
		if (str[i] == '\"')
			break ;
		else if (str[i] == '$' && str[i + 1])
			if (!(env = ft_get_env_value(shell, &str[i], &i, j)))
				continue ;
			else
				while (*env)
					word[++j] = *env++;
		else if (ft_strncmp(&str[i], "\\\"", 2) == 0)
			word[++j] = str[++i];
		else
			word[++j] = str[i];
	// if (!i)
	// 	word[++j] = ' ';
	word[++j] = '\0';
	*iterator += i + 1;
	if (str[i] != '\"')
		return (ft_exit_split("Error : need a double quote to finish the line.\n"));
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	
	return (word);
}

char	*ft_create_word_arg(t_shell *shell, t_split *s, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;
	char	*env;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i] && str[i] != '>' && str[i] != '<')
		if (str[i] == ' ' && (s->d_quotes % 2 == 0 && s->s_quotes % 2 == 0) && i != 0)
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
	if (ft_strlen(word) == 0)
		word[0] = '\0';
	if (s->d_quotes % 2 != 0 || s->s_quotes % 2 != 0)
		return (ft_exit_split("Error : need a quote to finish the line2.\n"));
	if (str[i] == '>' || str[i] == '<')
		i--;
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i;
	return (word);
}

char	*ft_create_word_simple_arg(t_shell *shell, char *str, int *iterator)
{
	char	*word;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!(word = malloc_lst(shell, sizeof(char) * (ft_strlen(str) + 1000))))
		return (NULL);
	while (str[++i])
		if (str[i] == '\'' && shell->split->s_quotes++)
			break ;
		else
			word[++j] = str[i];
	word[++j] = '\0';
	if (shell->split->s_quotes == 1)
		return (ft_exit_split("Error : need a quote to finish the line.\n"));
	shell->split->d_quotes = 0;
	shell->split->s_quotes = 0;
	*iterator += i + 1;
	return (word);
}

char	**ft_split_args_quotes(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	**res;

	if (!(res = malloc_lst(shell, sizeof(char *) * 40)))
		return (NULL);
	i = 0;
	j = -1;
	while (ft_strlen(str) >= i && str[i])
		if (str[i] == ' ')
			i++;
		else if ((str[i] == '>' || str[i] == '<') && i++ > -10)
		{
			if (str[i] == '>')
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
				i++;
		}
		else if (str[i] == '\"' && !shell->split->d_quotes++)
		{
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 0)
			{
				str[i] = ' ';
				//dprintf(1, "[%s]\n", &str[i]);
				res[++j] = ft_create_word_double_arg(shell, &str[i], &i);
			}
			else
			{
				res[++j] = ft_create_word_double_arg(shell, &str[++i], &i);
			}
			
		}
		else if (str[i] == '\'' && !shell->split->s_quotes++)
		{
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 0)
			{
					str[i] = ' ';
					res[++j] = ft_create_word_simple_arg(shell, &str[i], &i);
			}
			else
			{
				res[++j] = ft_create_word_simple_arg(shell, &str[++i], &i);
			}
			
		}
		
		else 
		{
			if (i - 1 >= 0 && str[i - 1] == ' ' && j != 0 && j != ft_strlen(str) - 1)
			{
					str[--i] = ' ';
					res[++j] = ft_create_word_arg(shell, shell->split, &str[i], &i);
			}
			else
			{
				res[++j] = ft_create_word_arg(shell, shell->split, &str[i++], &i);
			}
		}
	res[++j] = NULL;
	return (res);
}