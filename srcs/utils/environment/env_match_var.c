/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_match_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:59:28 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/17 15:37:38 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*replace_str_part(t_shell *shell, char *str, char *part, char *new_part)
{
	int 	i;
	char	*res;

	res = NULL;
	i = 0;
	while (str[i] && ft_strncmp(str + i, part, ft_strlen(part)))
		i++;
	if (str[i])
	{
		str[i] = 0;
		if (!new_part)
			return (str);
		if (!(res = ft_strjoin(str, new_part)) || !add_lst_to_free(shell, res))
			ft_exit_failure(shell, F_MALLOC, res);
		i += ft_strlen(part);
		if (str[i] && (!(res = ft_strjoin(res, str + i)) ||
			!add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
	}
	return (res);
}

static char	*replace_var_env_value(t_shell *shell, char *str, int *j, char *res)
{
	int		len;
	char	*var;
	char	*new_part;

	len = 1;
	if (!ft_isdigit(str[*j + 1]) && str[*j + 1] != '?')
		while (str[*j + len] != ' ' && str[*j + len]
			&& str[*j + len] != '=' && str[*j + len] != '$')	// autre char a checker ?
			len++;
	else
		len = 2;					
	if (!(var = ft_strdup(str + *j)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);	
	var[len] = 0;
	get_var_env(shell, var + 1, &new_part);
	res = replace_str_part(shell, res, var, new_part);
	*j += len;
	return (res);
}

static char	*replace_all_var_env_values(t_shell *shell, char *str)
{
	int		j;
	char	*res;

	if (!(res = ft_strdup(str)) || !add_lst_to_free(shell, res))
		ft_exit_failure(shell, F_MALLOC, res);	
	j = 0;	
	while (str[j])
	{
		while (str[j] != '$' && str[j])
			j++;
		if (str[j])
			res = replace_var_env_value(shell, str, &j, res);
	}
	return (res);
}

void		ft_match_var_env(t_shell *shell, t_tree *node)
{
	int		i;

	i = -1;
	while (node->args->args[++i])
	{
		if (node->args->var[i] == 1)
			node->args->args[i] = 
			replace_all_var_env_values(shell, node->args->args[i]);
	}
}
