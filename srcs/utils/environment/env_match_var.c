/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_match_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:59:28 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/19 12:52:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*replace_str_part(t_shell *shell, char *str, char *part, char *new_part)
{
	int 	i;
	char	*res;

// dprintf(1, "str = |%s|\npart = |%s|\nnew_part = |%s|\n", str, part, new_part);

	res = NULL;
	i = 0;
	while (str[i] && ft_strncmp(str + i, part, ft_strlen(part)))
		i++;

// dprintf(1, "str + i = |%s|\n\n", str + i);

	if (str[i])
	{
		str[i] = 0;
		if (!new_part &&
		(!(res = ft_strjoin(str, "")) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		if (new_part &&
			(!(res = ft_strjoin(str, new_part)) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		i += ft_strlen(part);
		if (str[i] && (!(res = ft_strjoin(res, str + i)) ||
			!add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
	}
	return (res);
}

static int	replace_var_env_value(t_shell *shell, char *str, int var_len, char **res)
{
	char	*var;
	char	*new_part;

	if (!(var = ft_strdup(str)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
	var[var_len + 1] = 0;
	get_var_env(shell, var + 1, &new_part);
	*res = replace_str_part(shell, *res, var, new_part);
	return (var_len + 1);
}

static char	*replace_all_var_env_values(t_shell *shell, char *str, t_var_status *lst)
{
	int		j;
	char	*res;

	if (!(res = ft_strdup(str)) || !add_lst_to_free(shell, res))
		ft_exit_failure(shell, F_MALLOC, res);	
	j = 0;
	// while (ft_strlen(str) >= j && str[j])
	while (str[j])
	{
		while (str[j] && str[j] != '$')
			j++;
		if (str[j])
		{

// dprintf(1, "lst_len = %d, str + j = |%s|\n", lst->len, str + j);
// dprintf(1, "res = |%s|\n", res);

			if (lst->len > 1)
			{
				j += replace_var_env_value(shell, str + j, lst->len - 1, &res);	// len a donner
				// j += lst->len;	// +1 ? a ajuster
			}
			else
				j++;
			lst = lst->next;	// on passe au next de la liste
		}
		
	}
	return (res);
}

void		ft_match_var_env(t_shell *shell, t_tree *node)
{
	int		i;

	i = -1;
	while (node->args->args[++i])
	{
		if (node->args->var[i] && node->args->args[i])
			node->args->args[i] = 
			replace_all_var_env_values(shell, node->args->args[i], node->args->var[i]);
	}
}

/*
static char	*replace_str_part(t_shell *shell, char *str, char *part, char *new_part)
{
	int 	i;
	char	*res;

// dprintf(1, "str = |%s|\npart = |%s|\nnew_part = |%s|\n", str, part, new_part);

	res = NULL;
	i = 0;
	while (str[i] && ft_strncmp(str + i, part, ft_strlen(part)))
		i++;

// dprintf(1, "str + i = |%s|\n\n", str + i);

	if (str[i])
	{
		str[i] = 0;
		if (!new_part &&
		(!(res = ft_strjoin(str, "")) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		if (new_part &&
			(!(res = ft_strjoin(str, new_part)) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		i += ft_strlen(part);
		if (str[i] && (!(res = ft_strjoin(res, str + i)) ||
			!add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
	}
	return (res);
}

static int	replace_var_env_value(t_shell *shell, char *str, int var_len, char **res)
{
	char	*var;
	char	*new_part;

	if (!(var = ft_strdup(str)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
	var[var_len + 1] = 0;
	get_var_env(shell, var + 1, &new_part);
	*res = replace_str_part(shell, *res, var, new_part);
	return (var_len + 1);
}

static char	*replace_all_var_env_values(t_shell *shell, char *str, int *tab)
{
	int		j;
	char	*res;

	if (!(res = ft_strdup(str)) || !add_lst_to_free(shell, res))
		ft_exit_failure(shell, F_MALLOC, res);	
	j = 0;
	while (ft_strlen(str) >= j && str[j])
	{
		while (str[j] && str[j] != '$')
			j++;
		if (str[j])
		{
			
			if (*tab > 0)
				j += replace_var_env_value(shell, str + j, *tab, &res);	// len a donner
			else
				j++;
			tab++;	// on passe au next de la liste
		}
		
	}
	return (res);
}

void		ft_match_var_env(t_shell *shell, t_tree *node)
{
	int		i;

	i = -1;
	while (node->args->args[++i])
	{
		if (node->args->var[i] && node->args->args[i])
			node->args->args[i] = 
			replace_all_var_env_values(shell, node->args->args[i], node->args->var[i]);
	}
}

*/