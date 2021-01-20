/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:40:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/20 10:02:53 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_new_arg(t_shell *shell, char **str, t_args *args, int *ind)
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


static int	add_new_arg(t_shell *shell, t_args *args, char **str, int *ind)
{
	if (**str == '<' || **str == '>' ||
		(**str == '2' &&  (*str)[1] == '>' && (*str)++))
		skip_redir(shell, str);
	else
		create_new_arg(shell, str, args, ind);

	while (**str == ' ')
		(*str)++;
	
	return (0);
}

static t_args	*init_args(t_shell *shell, char *str)
{
	t_args	*args;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!(args = malloc_lst(shell, sizeof(t_args))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(args->args = malloc_lst(shell, sizeof(char*) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(args->null = malloc_lst(shell, sizeof(int) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(args->var = malloc_lst(shell, sizeof(t_var_status*) * (len + 3) / 2)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = 0;
	while (i < (len + 3) / 2)
	{
		(args->args)[i] = NULL;
		(args->null)[i] = 1;
		(args->var)[i++] = NULL;
	}
	return (args);
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
