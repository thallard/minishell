/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:54:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/17 11:43:23 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_str_part(t_shell *shell, char *str, char *part, char *new_part)
{
	int 	i;
	char	*res;

	res = NULL;
	if (!str || !part)
		return (NULL);
	i = 0;
	while (str[i] && ft_strncmp(str + i, part, ft_strlen(part)))
		i++;
	if (str[i])
	{
		str[i] = 0;
		if (!new_part)
			return (str);
		if (!(res = ft_strjoin(str, new_part)) || !add_lst_to_free(shell, res))
			return (NULL);
		i += ft_strlen(part);
		if (str[i] && (!(res = ft_strjoin(res, str + i)) ||
			!add_lst_to_free(shell, res)))
			return (NULL);
	}
	return (res);
}

static char	*replace_var_env_value(t_shell *shell, char *str, int *j, char *res)
{
	int		len;
	char	*var;
	char	*new_part;

	len = 1;
	if (!ft_isdigit(str[*j + 1]))
		while (str[*j + len] != ' ' && str[*j + len]
			&& str[*j + len] != '=' && str[*j + len] != '$')	// autre char a checker ?
			len++;
	else
		len = 2;					
	if (!(var = ft_strdup(str + *j)) || !add_lst_to_free(shell, var))
		return (NULL);
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
		return (NULL);
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

static void	ft_match_var_env(t_shell *shell, t_tree *node)
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

int			launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	ft_match_var_env(shell, node);


	if (!(node->exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->args->args[0]));	// valeur de retour a confirmer
	if (manage_redirection(shell, node->dir) == FAILURE)
		return (FAILURE);	// a gerer avec errno

	if (is_builtin(node->args->args[0]))
		exec_builtin(shell, node, pipe_fd, is_pipe);
	else if (exec_execve(shell, node, pipe_fd, is_pipe) == FAILURE)
		return (FAILURE);
	ft_lstfd_close_clear(&shell->lst_fd);	// a mettre ici ?
	return (SUCCESS);								// valeur a confirmer
}

int			ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pipe(pipe_fd[1 - shell->last_pipe]);	// a verifier
	
	// dup2(pipe_fd[shell->last_pipe][0], pipe_fd[1 - shell->last_pipe][0]);
	// dup2(pipe_fd[shell->last_pipe][1], pipe_fd[1 - shell->last_pipe][1]);
	
	shell->last_pipe = 1 - shell->last_pipe;

	launch_exec(shell, node, pipe_fd, is_pipe);
	
	return (SUCCESS);
}
