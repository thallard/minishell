/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/20 15:39:14 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

t_env	*ft_prepare_lst_env(t_shell *shell, char *content, char *name)
{
	t_env	*new_lst;
	int		size;
	if (!content)
		size = 1;
	else
		size = ft_strlen(content);
	new_lst = NULL;
	if (!(new_lst = malloc_lst(shell, sizeof(t_env))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	new_lst->next = NULL;
	if (!(new_lst->name = malloc_lst(shell, sizeof(char) * ft_strlen(name) + 100)))
		ft_exit_failure(shell, F_MALLOC, new_lst->name);
	if (!(new_lst->content = malloc_lst(shell, sizeof(char) * size + 100)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	return (new_lst);
}

int		ft_filter_and_add(t_shell *shell, t_env *env, char *str, int j)
{
	int		k;

	k = 0;
	if (j <= ft_strlen(str) && ((char *)env->content)[0] != '\0' && env->hidden != 2)
		{
			if (str[j] == ' ')
				j = ft_strlen(str) + 1;
			while (str[j])
				((char *)env->content)[k++] = str[j++];
			((char *)env->content)[k] = '\0';
			//dprintf(1, "j'entre ici2\n");
			env->hidden = 0;
			replace_env_content(shell, env->name, env->content,  env->hidden);
		}
		else if (env->hidden != 2)
		{
	
			env->hidden = 1;
			((char *)env->content)[k] = '\0';
			
			replace_env_content(shell, env->name, env->content, env->hidden);
		}
		else if (env->hidden == 2)
		{
			((char *)env->content)[k] = '\0';
			//	dprintf(1, "j'entre ici4\n");
			replace_env_content(shell, env->name, env->content, env->hidden);
		}
	return (SUCCESS);
}

int		ft_get_arg_values_env(t_shell *shell, char **arg)
{
	int		i;
	int		j;
	t_env	*new_lst;
	// arg = ft_split_minishell_args(node->left->item, ' ', shell);
	//arg = node->args;
	i = 0;
	while (arg[++i])
	{
		//str = ft_split_quotes(shell, shell->split, arg[i]);
		new_lst = ft_prepare_lst_env(shell, arg[i], arg[i]);
		j = -1;
		while (arg[i][++j] && arg[i][j] != '=')
			new_lst->name[j] = arg[i][j];
		if (arg[i][j] == '=' && !arg[i][j + 1])
			new_lst->hidden = 2;
		else if (arg[i][j] != '=' && !arg[i][j])
			new_lst->hidden = 1;
		else
			new_lst->hidden = 0;
		new_lst->name[j++] = '\0';
		if ((j + 2) <= ft_strlen(arg[i]))
			if (ft_strncmp(&arg[i][j], "\"\"", 2) == 0 || ft_strncmp(&arg[i][j], "\'\'", 2) == 0)
				((char *)new_lst->content)[0] = '\0';

dprintf(1, "--> |%s|\n", arg[i]);
				
		ft_filter_and_add(shell, new_lst, arg[i], j);
	}
	return (SUCCESS);
}

int		ft_export(t_shell *shell, char **exec_args, char **tab_env)
{
	t_env	*sorted_env;

	sorted_env = NULL;
	(void)tab_env;
	//ft_print_tab_char(exec_args);
	if (exec_args[1])
	{
		if (ft_get_arg_values_env(shell, exec_args))
		{
			shell->exit = 0;
			return (SUCCESS);
		}
		else
		{
			shell->exit = 1;
			return (SUCCESS);
		}
	}
	else
	{
		sorted_env = ft_clone_export_env(shell->var_env);
		ft_sort_export_var(sorted_env);
		ft_print_export_var(sorted_env);
		ft_free_export_env(&sorted_env);
	}
		
	return (SUCCESS);
}
