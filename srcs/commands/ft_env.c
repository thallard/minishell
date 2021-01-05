/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:21:19 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 13:58:46 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

int		ft_env(t_shell *shell, t_tree *node)
{
	
	ft_printf("je suis dans env %s\n", node->left->item);
	return (SUCCESS);
}

int		ft_create_env_vars(t_shell *shell)
{
	// pid_t	program;
	// char	**tab;
	// // char	*newenviron[] = { "HOME=/",
    // //     "PATH=/Users/thallard/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/thallard/.brew/bin",
    // //     "TZ=UTC0",
    // //     "USER=thallard",
    // //     "LOGNAME=thallard", NULL };
	// char	*newenviron[] = {  NULL };

	// //tab = ft_split("/usr/bin/env > /Users/thallard/Documents/Cursus/minishell/fichier1", ' ');
	// tab = ft_split("/bin/bash ./srcs/commands/sh/get_env.sh", ' ');
	// //dprintf(1, "[%s] [%s] [%s]\n", tab[0], tab[1], tab[2]);
	// if (program == fork())
	// 	execve(tab[0], tab, newenviron);
	// dprintf(1, "oui\n");
	ft_fill_lst_env(shell);
	return (1);
}

int		ft_fill_lst_env(t_shell *shell)
{
	int		fd;
	char	str[10000];
	int		i;
	int		j;
	int		k;

	if ((ft_fill_tab_env(shell) < 0))
		return (FAILURE);
	i = -1;
	while (shell->tab_env[++i])
	{
		ft_bzero(str, ft_strlen(str));
		j = -1;
		shell->var_env = malloc_lst(shell, sizeof(t_env));
		while (shell->tab_env[i][++j] && shell->tab_env[i][j] != '=')
			str[j] = shell->tab_env[i][j];
		str[j] = '\0';
		if (!(shell->var_env->name = ft_strdup(str)))
			return (FAILURE);
		if (!(add_lst_to_free(shell, shell->var_env->name)))
			return (FAILURE);
		shell->var_env->content = ft_fill_env_content(shell, &shell->tab_env[i][j + 1]);
		if (!shell->var_env->content)
			return (FAILURE);
// dprintf(1, "%s=%s\n", shell->var_env->name, shell->var_env->content);
		shell->var_env = shell->var_env->next;
	}
	
	// while ((get_next_line(fd, &line)) > 0)
	// {
	// 	shell->var_env = malloc_lst(shell, sizeof(t_env));
	// 	//dprintf(1, "dans gnl1 \n");
	// 	i = -1;
	// 	while (line[++i] && line[i] != '=')
	// 		str[i] = line[i];
	// 	str[i] = '\0';
		
	// 		//dprintf(1, "dans gnl2 \n");
	// 	shell->var_env->name = ft_strdup(str);
	// 	ft_bzero(str, ft_strlen(str));
	// 	//dprintf(1, "dans gnl3 %s\n", shell->var_env->name);
	// 	i++;
	// 	j = 0;
	// 	while (line[i])
	// 		str[j++] = line[i++];
	// 	str[j] = '\0';
	// 	shell->var_env->content = ft_strdup(str);
	// 	dprintf(1, "Name : %s et content : %s\n", shell->var_env->name, shell->var_env->content);
	// 	shell->var_env = shell->var_env->next;
		
	// 	//free(line);
	// }
	return (1);
}

char	*ft_fill_env_content(t_shell *shell, char *str)
{
	char	*content;
	int		i;

	if (!(content = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	if (!(add_lst_to_free(shell, content)))
		return (NULL);
	i = -1;
	while (str[++i])
		content[i] = str[i];
	content[i] = '\0';
	return (content);
}

int		ft_fill_tab_env(t_shell *shell)
{
	int				fd;
	char			str_file[10000];
	struct stat		fd_status;

	if (stat("env_file", &fd_status) == -1)
		return (FAILURE);
	fd = open("env_file", O_RDONLY);
	read(fd, str_file, 10000);
	if (!(shell->tab_env = ft_split(str_file, '\n')))
		return (FAILURE);
	if (!(add_lst_to_free(shell, shell->tab_env)))
		return (FAILURE);
	return (SUCCESS);
}
