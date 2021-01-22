/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_match_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:59:28 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:59:43 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_new_part(t_shell *shell, char *part)
{
	char	*new_part;

	if (part[1] == 0 && ((!(new_part = ft_strdup("\\$"))) ||
								!add_lst_to_free(shell, new_part)))
		ft_exit_failure(shell, F_MALLOC, new_part);
	if (ft_isdigit(part[1]) && ((!(new_part = ft_strdup(""))) ||
								!add_lst_to_free(shell, new_part)))
		ft_exit_failure(shell, F_MALLOC, new_part);
	if (part[1] == '?' && ((!(new_part = ft_itoa(shell->exit))) ||
								!add_lst_to_free(shell, new_part)))
		ft_exit_failure(shell, F_MALLOC, new_part);
	if (part[1] == '\\' && ((!(new_part = ft_strdup("$"))) ||
								!add_lst_to_free(shell, new_part)))
		ft_exit_failure(shell, F_MALLOC, new_part);
	if (!ft_isdigit(part[1]) && part[1] != '?' && part[1] != '\\' && part[1])
		get_var_env(shell, part + 1, &new_part, 1);
	return (new_part);
}

static char	*replace_str_part(t_shell *shell, char *str, char *part, int *j)
{
	int		i;
	char	*res;
	char	*new;

	i = *j;
	res = NULL;
	if ((new = get_new_part(shell, part)))
		*j += ft_strlen(new);
	while (str[i] && ft_strncmp(str + i, part, ft_strlen(part)))
		i++;
	if (str[i])
	{
		str[i] = 0;
		if (!new &&
		(!(res = ft_strjoin(str, "")) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		if (new &&
			(!(res = ft_strjoin(str, new)) || !add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
		i += ft_strlen(part);
		if (str[i] && (!(res = ft_strjoin(res, str + i)) ||
			!add_lst_to_free(shell, res)))
			ft_exit_failure(shell, F_MALLOC, res);
	}
	return (res);
}

static void	replace_var_env_value(t_shell *shell, char *str, char **res, int *j)
{
	char	*var;
	int		var_len;

	var_len = shell->lst_var_len->len - 1;
	if (!(var = ft_strdup(str)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
	var[var_len + 1] = 0;
	*res = replace_str_part(shell, *res, var, j);
}

static char	*replace_all_var_env_values(t_shell *shell, char *str, int export)
{
	int		j;
	char	*res;

	if (!(res = ft_strdup(str)) || !add_lst_to_free(shell, res))
		ft_exit_failure(shell, F_MALLOC, res);
	j = 0;
	while (*str)
	{
		while (*str && *str != '$' && ++j)
			str++;
		if (*str)
		{
			if (shell->lst_var_len->len > 1)
			{
				replace_var_env_value(shell, str, &res, &j);
				str += shell->lst_var_len->len;
			}
			else if (shell->lst_var_len->len == -1 && export && str++)
				res = replace_str_part(shell, res, "$", &j);
			else
				str++;
			shell->lst_var_len = shell->lst_var_len->next;
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
		{
			shell->lst_var_len = node->args->var[i];
			node->args->args[i] =
			replace_all_var_env_values(shell, node->args->args[i],
					!ft_strncmp(node->args->args[0], "export", 7));
			if (!ft_strncmp(node->args->args[i], "", 1))
				node->args->null[i] = 0;
		}
	}
	i = -1;
	while (node->dir[++i].file)
	{
		if (node->dir[i].var && node->dir[i].file)
		{
			shell->lst_var_len = node->dir[i].var;
			node->dir[i].file =
			replace_all_var_env_values(shell, node->dir[i].file, 0);
		}
	}
}
