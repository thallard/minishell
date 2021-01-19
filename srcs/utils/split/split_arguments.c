/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:40:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 12:51:04 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_redir_quotes_char(char c)
{
	if (!c || c == ' ' || c == '<' || c == '>' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	skip_quotes(t_shell *shell, char **str)
{
	char	c;

	c = **str;
	while (**str && **str != c)
		(*str)++;
	if (!(**str))
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	return (1);
}

int	skip_char_redir(t_shell *shell, char **str)
{
	while (!is_redir_quotes_char(**str))
		(*str)++;
	if (!(**str) || **str == ' ' || **str == '<' || **str == '>')
		return (1);
	skip_quotes(shell, str);
	(*str)++;
	skip_char_redir(shell, str);
	return (0);
}

int	skip_redir(t_shell *shell, char **str)
{
	if ((*str)[0] == '>' && (*str)[1] == '>')
		(*str)++;
	(*str)++;
	while (**str == ' ')
		(*str)++;
	skip_char_redir(shell, str);
	return (1);
}

t_args	*init_args(t_shell *shell, char *str)
{
	t_args	*args;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!(args = malloc_lst(shell, sizeof(t_args))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(args->args = malloc_lst(shell, sizeof(char*) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(args->var = malloc_lst(shell, sizeof(t_var_status*) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;

// dprintf(1, "nb cases = %d\n", (len + 3) / 2);

	while (i < (len + 3) / 2)
	{

// dprintf(1, "i = %d\n", i);

		(args->args)[i] = NULL;
		(args->var)[i++] = NULL;
	}
	return (args);
}




void	add_var_env_status_normal(t_shell *shell, char *part, t_args *args, int ind)
{
	int	len;

// dprintf(1, "add var env - |%s|\n", part);

	while (*part)
	{
		if (*part == '$')
		{
			part++;
			len = 1;
			// while (*part && *part != '$' && *part != '=')	// $$ a gerer differement
			while (*part && ft_isalnum(*part))	// $$ a gerer differement
			{
				part++;
				len++;
			}
			ft_lstvaradd_back(shell, args, len, ind);
		}
		else
			part++;
	}
}

void	add_var_env_status_simple_quote(t_shell *shell, char *part, t_args *args, int ind)
{
	int	len;

dprintf(1, "add var env simple - |%s|\n", part);


	while (*part)
	{
		if (*part == '$')
		{
			part++;
			len = 1;
			// while (*part && *part != '$' && *part != '=')	// $$ a gerer differement
			while (*part && ft_isalnum(*part))	// $$ a gerer differement
			{
				part++;
				len++;
			}
			ft_lstvaradd_back(shell, args, 1, ind);
		}
		else
			part++;
	}
}

char	*create_new_arg_part_normal(t_shell *shell, char **str, t_args *args, int ind)
{
	char	*arg_part;
	int		i;

	i = 0;
	while (!is_redir_quotes_char((*str)[i]))
		i++;
	if (!(arg_part = malloc_lst(shell, i + 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	while (!is_redir_quotes_char(**str))
		arg_part[i++] = *((*str)++);
	arg_part[i] = 0;
	add_var_env_status_normal(shell, arg_part, args, ind);
	return (arg_part);
}

char	*create_new_arg_part_quote(t_shell *shell, char **str, t_args *args, int ind)
{
	char	*arg_part;
	int		i;
	char	c;

	c = **str;
	i = 1;
	while ((*str)[i] && ((*str)[i] != c || (*str)[i - 1] == '\\'))
		i++;
		
	if (!(*str)[i])
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	if (!(arg_part = malloc_lst(shell, i + 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	(*str)++;
	while (**str != c)	// normalemet \ pris en compte en dessous
	{
		if (**str == '\\' && ((*str)[1] == c || (*str)[1] == '\\'))
			(*str)++;
		arg_part[i++] = *((*str)++);
	}
	arg_part[i] = 0;
	(*str)++;
	if (c == '\"')
		add_var_env_status_normal(shell, arg_part, args, ind);
	else
		add_var_env_status_simple_quote(shell, arg_part, args, ind);
	return (arg_part);
}

void	create_new_arg(t_shell *shell, char **str, t_args *args, int *ind)
{
	// char 	*str_arg;
	char	*arg_part;

	if (!(args->args[*ind] = malloc_lst(shell, 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	args->args[*ind][0] = 0;
	while (**str && **str != ' ' && **str != '<' && **str != '>')
	{
		if (**str != '\'' && **str != '\"')
			arg_part = create_new_arg_part_normal(shell, str, args, *ind);
		else
			arg_part = create_new_arg_part_quote(shell, str, args, *ind);
		if (!(args->args[*ind] = ft_strjoin(args->args[*ind], arg_part)) ||
			!add_lst_to_free(shell, args->args[*ind]))
			ft_exit_failure(shell, F_MALLOC, NULL);
	}
	(*ind)++;
}

int	add_new_arg(t_shell *shell, t_args *args, char **str, int *ind)
{
	if (**str == '<' || **str == '>')
		skip_redir(shell, str);
	else
		create_new_arg(shell, str, args, ind);

	while (**str == ' ')
		(*str)++;
	
	return (0);
}

t_args	*split_arguments(t_shell *shell, char *str)
{
	t_args	*args;
	int		ind;
	
	if (!str)
		return (NULL);
	args = init_args(shell, str);
	while (*str == ' ')
		str++;
	ind = 0;
	while (*str)
		add_new_arg(shell, args, &str, &ind);

	return (args);
}