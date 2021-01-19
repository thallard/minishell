/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:04:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 17:00:23 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_var_env_status_normal(t_shell *shell, char *part, t_args *args, int ind)
{
	int	len;

	while (*part)
	{
		if (ft_abs(*part) == '$')
		{
			if (*part < 0 && (*part = '$'))
				ft_lstvaradd_back(shell, args, 1, ind);
			part++;
			len = 1;
			if ((ft_isdigit(*part) || *part == '?') && len++)
				part++;
			else
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

static void	add_var_env_status_simple_quote(t_shell *shell, char *part, t_args *args, int ind)
{
	while (*part)
	{
		if (*part == '$')
		{
			part++;
			while (*part && ft_isalnum(*part))	// $$ a gerer differement
				part++;
			ft_lstvaradd_back(shell, args, 1, ind);
		}
		else
			part++;
	}
}

static char	*create_new_arg_part_normal(t_shell *shell, char **str, t_args *args, int ind)
{
	char	*arg_part;
	int		i;
	int		len;

	len = 0;
	while (!is_redir_quotes_char((*str)[len]))
	{
		if ((*str)[len] == '\\' && (*str)[len + 1] && (*str)[len + 1] != ' ')
			len++;
		len++;
	}
	if (!(arg_part = malloc_lst(shell, len + 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	while (i < len)
	{
		if (**str == '\\')
			(*str)++;
		arg_part[i++] = *((*str)++);
	}
	arg_part[i] = 0;
	add_var_env_status_normal(shell, arg_part, args, ind);
	return (arg_part);
}

static char	*create_new_arg_part_double_quote(t_shell *shell, char **str, t_args *args, int ind)
{
	char	*arg_part;
	int		i;

	i = 1;
	while ((*str)[i] && ((*str)[i] != '\"' || (*str)[i - 1] == '\\'))
		i++;
	if (!(*str)[i])
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	if (!(arg_part = malloc_lst(shell, i + 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	(*str)++;
	while (**str != '\"')
	{
		if (**str == '\\' && (*str)[1] == '$' && ((*str)[1] = -36))
			(*str)++;
		else if (**str == '\\')
			(*str)++;
		arg_part[i++] = *((*str)++);
	}
	arg_part[i] = 0;
	(*str)++;
	add_var_env_status_normal(shell, arg_part, args, ind);
	return (arg_part);
}

static char	*create_new_arg_part_simple_quote(t_shell *shell, char **str, t_args *args, int ind)
{
	char	*arg_part;
	int		i;

	i = 1;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	if (!(*str)[i])
		ft_exit_split(shell, "Error : need a quote to finish the line.\n");
	if (!(arg_part = malloc_lst(shell, i + 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	(*str)++;
	while (**str != '\'')
		arg_part[i++] = *((*str)++);
	arg_part[i] = 0;
	(*str)++;
	add_var_env_status_simple_quote(shell, arg_part, args, ind);
	return (arg_part);
}

void	create_new_arg(t_shell *shell, char **str, t_args *args, int *ind)
{
	char	*arg_part;

	if (!(args->args[*ind] = malloc_lst(shell, 1)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	args->args[*ind][0] = 0;
	while (**str && **str != ' ' && **str != '<' && **str != '>')
	{
		if (**str != '\'' && **str != '\"')
			arg_part = create_new_arg_part_normal(shell, str, args, *ind);
		else if (**str == '\"')
			arg_part = create_new_arg_part_double_quote(shell, str, args, *ind);
		else
			arg_part = create_new_arg_part_simple_quote(shell, str, args, *ind);
		if (!(args->args[*ind] = ft_strjoin(args->args[*ind], arg_part)) ||
			!add_lst_to_free(shell, args->args[*ind]))
			ft_exit_failure(shell, F_MALLOC, args->args[*ind]);
	}
	(*ind)++;
}
