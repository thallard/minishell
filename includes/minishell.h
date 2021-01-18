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

# define F_MALLOC 12
# define NO_EXEC_PATH 4
# define F_FORK 10

# define PIPE_OUT 1
# define PIPE_IN 2
# define PIPE_STDIN 5

# define PARENT 1
# define CHILD 0


# define PRINT_HEADER 0

typedef struct 		s_args
{
	char	**args;
	int		**var;
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
}					t_dir;

typedef struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_args			*args;
	// char			**args;
	t_dir			**dir;
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
}					t_shell;

/*
****************************************************
**					  COMMANDS					  **
****************************************************
*/
/*
** Commands
*/
int		ft_cd(t_shell *shell, char **exec_args, char **tab_env);
int		ft_echo(t_shell *shell, char **exec_args, char **tab_env);
int		ft_env(t_shell *shell, char **exec_args, char **tab_env);
int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env);
int		ft_unset(t_shell *shell, char **exec_args, char **tab_env);
int		ft_export(t_shell *shell, char **exec_args, char **tab_env);
void	ft_exit(t_shell *shell, char **exec_args, char **tab_env);
void	ft_exit_failure(t_shell *shell, int int_failure, void *ptr);

/*
****************************************************
**						MAIN					  **
****************************************************
*/

/*
** ft_ctrl.c
*/
void	ft_ctrl_c(int sign);
void	ft_ctrl_back(int sign);

/*
** minishell.c
*/

/*
** redirection.c
*/
void	manage_redirection(t_shell *shell, t_dir **exec_dir);


/*
****************************************************
**						TREE					  **
****************************************************
*/

/*
** exec_builtin_execve.c
*/
int		exec_builtin(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);
int		exec_execve(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);

/*
** node_exec.c
*/
int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);
int		ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);

/*
** tree_build.c
*/
int		read_input(t_shell *shell, t_tree **t_current, char **input);
int		create_main_tree(t_shell *shell, char *input);

/*
** tree_read.c
*/
int		is_builtin(char *exec);
int		read_tree(t_shell *shell);

/*
****************************************************
**						UTILS					  **
****************************************************
*/

/*
** clear_objects.c
*/
void	*add_lst_to_free(t_shell *shell, void *ptr);
void	*malloc_lst(t_shell *shell, int size);
int		free_all_ptr(t_shell *shell);
void	ft_free_export_env(t_env **env);
void	ft_lstfd_close_clear(t_fd **lst);

/*
** print_return.c
*/
void	print_header(int fd);
void	print_error_and_exit(t_shell *shell, char *cmd, int int_failure);
int		print_error(t_shell *shell, char *cmd);
void	ft_exit_split(t_shell *shell, char *str);

/*
** print_return_2.c
*/
int		print_oldpwd_error(t_shell *shell, char *cmd);
int		print_unset_error(t_shell *shell, char *cmd);
int		ft_cmd_not_found(t_shell *shell, char *exec);
int		find_sep_error(char *str);
int		print_sep_error(t_shell *shell, int err);

/*
**--------------------
**		env			**
**--------------------
*/
/*
** env_fill.c
*/
void	ft_swap_env_all(t_env *a, t_env *b);
void	ft_swap_env_content(t_env *a, t_env *b);
int		ft_fill_lst_env(t_shell *shell, char **envp);
t_env	*ft_prepare_lst_env(t_shell *shell, char *content, char *name);

/*
** env_match_var.c
*/
void	ft_match_var_env(t_shell *shell, t_tree *node);
int		ft_lst_env_size(t_env *env);

/*
** env_replace_value.c
*/
int		ft_add_new_env(t_shell *shell, char *name, char *content);
char	*ft_get_env_value(t_shell *shell, char *txt, int *j, int i);
int		replace_env_content(t_shell *shell, char *name, char *content, int hidden);

/*
** env_utils.c
*/
void	ft_env_add_back(t_env **alst, t_env *new);
void	ft_print_env_var(t_env *var_end);
void	ft_print_export_var(t_env *var_end);
void	ft_remove_elem(t_env **ptr_back, t_env **ptr);

/*
** env_utils2.c
*/
t_env	*ft_get_var_env(t_shell *shell, char *name);
void	ft_env_remove_if(t_env **begin_list, void *name_ref,
		int (*cmp)());
int		get_var_env(t_shell *shell, char *var_name, char **content);
void	ft_sort_export_var(t_env *env);
t_env	*ft_clone_export_env(t_env *lst);

/*
**--------------------
**		splits		**
**--------------------
*/
/*
** All splits 
*/
char		**ft_split_quotes(t_shell *shell, t_split *s, char *str);
char		*ft_create_word(t_shell *shell, t_split *s, char *str, int *iterator);
t_dir		**ft_split_redirection(t_shell *shell, char *str);
t_dir		**ft_split_minishell_dir(char const *s, char c, t_shell *shell);
char		**ft_split_args_quotes(t_shell *shell, char *str);
char		**ft_split_exec_paths(char const *s, char c, t_shell *shell);
t_args		*ft_split_args(t_shell *shell, char *str);


/*
** Utils for splits
*/
int			ft_get_nb_env(t_shell *shell, char *str);
char		*ft_create_word_simple_dir(t_shell *shell, char *str, int *iterator);
char		*ft_create_word_double_dir(t_shell *shell, char *str, int *iterator);
char		*ft_create_word_dir(t_shell *shell, t_split *s, char *str, int *iterator);
int			is_redirection(char *str, int i);
int			ft_fill_split_env(char *str);
int			ft_add_dir_error(t_shell *shell, char *str_bis);
t_dir		*ft_add_redirection(t_shell *shell, char *str, int *i, int *j);

/*
**--------------------
**		 str		**
**--------------------
*/
/*
** str_utils_op_sep_space.c
*/
int		is_separator(char c);
int		skip_spaces(char **str);
void	str_to_separator(char **str);
char	*strdup_and_inc_input(t_shell *shell, char **input);

/*
** str_utils.c
*/
int		ft_strrfind(const char *s, int c);
char	*ft_remove_eol(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2, int f_s1, int f_s2);


/*
****************************************************
**						DRAFT					  **
****************************************************
*/

/*
** print_functions.c // A SUPPRIMER
*/
void	ft_print_tree(t_tree *node, int nb); // a supprimer
void	ft_print_tab_char(char **tab);
void	ft_print_tab_dir(t_dir **dir);


#endif