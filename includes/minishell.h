/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:30:08 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 14:45:33 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/printf/includes/printf.h"

# define SUCCESS 1
# define FAILURE -1

# define OP 1
# define SEP 2

# define NOT_ENOUGH_ARG 3
# define TOO_MANY_ARG 4

# define DOUBLE_SEP_V -2
# define DOUBLE_SEP_DV -3
# define DOUBLE_SEP_P -4
# define DOUBLE_SEP_DP -5
# define CHAR_DIR_ERR -6

# define F_MALLOC 12
# define NO_EXEC_PATH 4
# define F_FORK 10

# define PIPE_OUT 1
# define PIPE_IN 2
# define PIPE_STDIN 5

# define PARENT 1
# define CHILD 0

# define TO_PRINT 0
# define NOT_PRINT 1
# define UNSET 2

# define PRINT_HEADER 0

typedef struct		s_var_s
{
	struct s_var_s	*next;
	int				len;
}					t_var_s;

typedef struct		s_args
{
	char			**args;
	int				*null;
	t_var_s			**var;
}					t_args;

typedef struct		s_fd
{
	struct s_fd		*next;
	int				fd;
}					t_fd;

typedef struct		s_dir
{
	int				dir;
	char			*file;
	t_var_s			*var;
}					t_dir;

typedef struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_args			*args;
	t_dir			*dir;
	char			*exec_path;
}					t_tree;

typedef struct		s_env
{
	char			*name;
	void			*content;
	int				hidden;
	struct s_env	*next;
}					t_env;

typedef struct		s_split
{
	int				d_quotes;
	int				s_quotes;
	int				env;
}					t_split;

typedef struct		s_shell
{
	int				exit;
	t_env			*var_env;
	char			**tab_env;
	t_list			*ptrs;
	t_tree			*root;
	char			*input;
	int				last_node;
	char			*op;
	char			*sep;
	t_split			*split;
	int				last_pipe;
	int				std[3];
	t_fd			*lst_fd;
	char			*buffer_std;
	char			*dir_err;
	char			char_dir_error;
	t_var_s			*lst_var_len;
}					t_shell;

/*
****************************************************
**					  COMMANDS					  **
****************************************************
*/
/*
** Commands
*/
int					ft_cd(t_shell *shell, char **exec_args, char **tab_env);
int					ft_echo(t_shell *shell, char **exec_args, int *tab_null);
void				ft_add_env_export_dollar(t_shell *shell, char *str);
int					ft_env(t_shell *shell, char **exec_args, char **tab_env);
int					ft_pwd(t_shell *shell, char **exec_args, char **tab_env);
int					ft_unset(t_shell *shell, char **exec_args, char **tab_env);
int					ft_export(t_shell *shell, char **exec_args, char **tab_env);
int					ft_exit(t_shell *shell, char **exec_args, char **tab_env);
void				ft_exit_failure(t_shell *shell, int int_failure, void *ptr);

/*
** ft_cd_utils.c
*/
int					get_correct_return(int res);
char				*build_path(t_shell *shell, char *current_path,
								char *folder);
void				maj_pwd_and_oldpwd(t_shell *shell, char **exec_args);

/*
****************************************************
**						MAIN					  **
****************************************************
*/

/*
** ft_ctrl.c
*/
void				ft_ctrl_c(int sign);
void				ft_ctrl_back(int sign);

/*
** redirection.c
*/
int					manage_redirection(t_shell *shell, t_dir *exec_dir);

/*
****************************************************
**						TREE					  **
****************************************************
*/

/*
** exec_builtin_execve.c
*/
int					exec_builtin(t_shell *shell, t_tree *node,
								int pipe_fd[2][2], int is_pipe);
int					exec_execve(t_shell *shell, t_tree *node, int pipe_fd[2][2],
								int is_pipe);

/*
** node_exec.c
*/
int					launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2],
								int is_pipe);

/*
** tree_build.c
*/
int					read_input(t_shell *shell, t_tree **t_current,
								char **input);
int					create_main_tree(t_shell *shell, char *input);

/*
** tree_read.c
*/
int					ft_exec_and_pipe(t_shell *shell, t_tree *node,
									int pipe_fd[2][2], int is_pipe);
int					is_builtin(char *exec);
int					read_tree(t_shell *shell);

/*
****************************************************
**						UTILS					  **
****************************************************
*/

/*
** clear_objects.c
*/
void				*add_lst_to_free(t_shell *shell, void *ptr);
void				*malloc_lst(t_shell *shell, int size);
int					free_all_ptr(t_shell *shell);
void				ft_lstfd_close_clear(t_fd **lst);

/*
** print_return.c
*/
void				print_header(int fd);
void				print_error_and_exit(t_shell *shell, char *cmd,
										int int_failure);
int					print_error(t_shell *shell, char *cmd, int exit_status);
int					print_exit_error(t_shell *shell, char *arg, char *text,
									int exit_status);
void				ft_exit_split(t_shell *shell, char *str);

/*
** print_return_2.c
*/
int					print_oldpwd_error(t_shell *shell, char *cmd);
int					print_unset_error(t_shell *shell, char *cmd);
int					ft_cmd_not_found(t_shell *shell, char *exec, t_tree *node);
int					find_sep_error(char *str);
int					print_sep_error(t_shell *shell, int err);

/*
** stds_utils.c
*/
int					reset_stds(t_shell *shell);
int					print_dir_error(t_shell *shell, char *cmd);
int					print_dir_file_error(t_shell *shell, char *cmd);

/*
**--------------------
**		env			**
**--------------------
*/
/*
** env_fill_lst_and_swap.c
*/
void				ft_swap_env_all(t_env *a, t_env *b);
void				ft_swap_env_content(t_env *a, t_env *b);
int					ft_fill_lst_env(t_shell *shell, char **envp);
t_env				*ft_prepare_lst_env(t_shell *shell, char *content,
										char *name);
char				*ft_fill_env_content(t_shell *shell, char *str);

/*
** env_match_var.c
*/
void				ft_match_var_env(t_shell *shell, t_tree *node);
int					ft_lst_env_size(t_env *env);

/*
** env_replace_value.c
*/
void				change_last_arg_env(t_shell *shell, t_tree *node);
int					ft_add_new_env(t_shell *shell, char *name, char *content,
									int hidden);
void				ft_change_value_tab_env(t_shell *shell, char ***tab_env,
										char *name, char *content);
int					replace_env_content(t_shell *shell, char *name,
										char *content, int hidden);
int					ft_prepare_hidden_name_export(t_shell *shell, t_env **env,
												char *arg, int j);
int					ft_add_value_to_existent_env(t_shell *shell, t_env *env,
												char *str);
int					ft_filter_and_add(t_shell *shell, t_env *env, char *str,
										int j);
t_args				*ft_finish_fill_env(t_shell *shell, char *str,
										t_env **new_lst, char *arg);

/*
** env_print_and_addlast.c
*/
void				ft_env_add_back(t_env **alst, t_env *new);
void				ft_print_env_var(t_env *var_end);
void				ft_print_export_var(t_env *var_end);
void				ft_remove_elem(t_env **ptr_back, t_env **ptr);

/*
** env_utils2.c
*/
t_env				*ft_get_var_env(t_shell *shell, char *name);
int					get_var_env(t_shell *shell, char *var_name, char **content,
								int unset);
void				ft_sort_export_var(t_env *env);
t_env				*ft_clone_export_env(t_shell *shell, t_env *lst);

/*
** env_utils3.c
*/
int					ft_prepare_env(int unset, t_env *begin, char *var_name,
									char **content);
char				*ft_prepare_tab_change_value(t_shell *shell, char *name,
												int *i);

/*
** env_unset_utils.c
*/
int					ft_unset_hide_env(t_shell *shell, t_env **env, char *name);
int					char_not_valid(char *str);
int					ft_set_shlvl(t_shell *shell);

/*
**--------------------
**		split		**
**--------------------
*/

/*
** split_args_utils_lst.c
*/
t_var_s				*ft_lstvaradd_back(t_shell *shell, t_args *args, int len,
										int ind);
t_var_s				*ft_lstvaradd_back_dir(t_shell *shell, t_dir *dir,
											int len, int ind);

/*
** split_args_utils_skip.c
*/
int					is_redir_quotes_char(char c);
int					skip_quotes(t_shell *shell, char **str);
int					skip_redir(t_shell *shell, char **str);
int					skip_arg(t_shell *shell, char **str);

/*
** split_args_utils.c
*/
int					add_var_env_status_normal(t_shell *shell, char *part,
												t_args *args, int ind);
void				add_var_env_status_simple_quote(t_shell *shell, char *part,
												t_args *args, int ind);
char				*create_new_arg_part_normal(t_shell *shell, char **str,
													t_args *args, int ind);
char				*create_new_arg_part_double_quote(t_shell *shell,
											char **str, t_args *args, int ind);

/*
** split_args.c
*/
char				*create_new_arg_part_simple_quote(t_shell *shell,
										char **str, t_args *args, int ind);
t_args				*split_arguments(t_shell *shell, char *str);

/*
** split_dir_utils_skip.c
*/
int					skip_arg(t_shell *shell, char **str);

/*
** split_dir_utils.c
*/
char				*create_new_dir_part_normal(t_shell *shell, char **str,
													t_dir *dir, int ind);
char				*create_new_dir_part_double_quote(t_shell *shell,
											char **str, t_dir *dir, int ind);
char				*create_new_dir_part_simple_quote(t_shell *shell,
											char **str, t_dir *dir, int ind);

/*
** split_dir.c
*/
t_dir				*split_redirection(t_shell *shell, char *str);

/*
** split_exec_paths.c
*/
char				**ft_split_exec_paths(char const *s, char c,
										t_shell *shell);

/*
** split_utils.c
*/
void				fill_arg_part_double_quote(char **str, char *arg_part);
int					is_redirection(char **str);

/*
**--------------------
**		 str		**
**--------------------
*/
/*
** str_utils_op_sep_space.c
*/
int					is_separator(char c);
int					skip_spaces(char **str);
void				str_to_separator(char **str);
char				*strdup_and_inc_input(t_shell *shell, char **input);

/*
** str_utils.c
*/
int					ft_strrfind(const char *s, int c);
char				*ft_remove_eol(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp_lower(const char *s1, const char *s2,
									unsigned int n);
char				*ft_strjoin_free(char *s1, char *s2, int f_s1, int f_s2);

#endif
