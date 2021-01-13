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
# define EOL 0

# define OP 1
# define SEP 2

# define NOT_ENOUGH_ARG 3
# define TOO_MANY_ARG 4

# define DOUBLE_SEP -2

# define PIPE_OUT 1
# define PIPE_IN 2
# define PIPE_STDIN 5

# define PARENT 1
# define CHILD 0

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
	char			**args;
	t_dir			**dir;
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
	int		s_quotes;
	int		d_quotes;
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
	int				std[2];
	t_fd			*lst_fd;
}					t_shell;

/*
****************************************************
**						MAIN					  **
****************************************************
*/

/*
** minishell.c
*/
int		init_shell(t_shell *shell);
int		ft_exec(t_shell *shell, char *exec_path, char **exec_args, int to_print);

/*
** redirection.c
*/
void	ft_lstfd_close_clear(t_fd **lst);
int		manage_redirection(t_shell *shell, t_dir **exec_dir);


/*
****************************************************
**						TREE					  **
****************************************************
*/

/*
** tree_build.c
*/
t_tree	*tree_create_node(t_shell *shell, char **args, t_dir **dir);
int		add_op_node(t_shell *shell, t_tree *t_current, char **input);
int		add_sep_node(t_shell *shell, t_tree **t_current, char **input);
int		read_input(t_shell *shell, t_tree **t_current, char **input);
int		create_main_tree(t_shell *shell, char *input);

/*
** tree_get_arg.c
*/
int		get_nb_operand_arg(char *op);
t_tree	*get_next_arg_echo(t_shell *shell,char **input, int nb_arg);
int		get_echo_arg(t_shell *shell, char **input, t_tree *op_node);
t_tree	*get_next_arg(t_shell *shell,char **input);
int		get_operand_arg(t_shell *shell, char **input, t_tree *op_node);

/*
** tree_read.c
*/
char	*is_exec_in_path(char *exec, char *folder_path);
char	*find_exec(t_shell *shell, t_tree *node);
char	**get_exec_args(t_shell *shell, char *exec, char *args, int is_pipe);
int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);
int		ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe);
int		read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in);
int		read_tree(t_shell *shell);

/*
** redirection.c
*/
int		manage_redirection(t_shell *shell, t_dir **exec_dir);


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

/*
** print_return.c
*/
int		print_unset_error(t_shell *shell, char *cmd);
int		ft_cmd_not_found(t_shell *shell, char *exec);
int		print_cd_error(t_shell *shell, char *cmd);
char	*ft_exit_split(char *str);

/*
** All splits 
*/
char		**ft_split_quotes(t_shell *shell, t_split *s, char *str);
char		*ft_create_word(t_shell *shell, t_split *s, char *str, int *iterator);
t_dir		**ft_split_redirection(t_shell *shell, char *str);
char		**ft_split_minishell_args(char const *s, char c, t_shell *shell);
t_dir		**ft_split_minishell_dir(char const *s, char c, t_shell *shell);
char		**ft_split_args_quotes(t_shell *shell, char *str);

/*
** str_utils.c
*/
int		ft_strrfind(const char *s, int c);
char	*ft_remove_eol(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2, int f_s1, int f_s2);

/*
** str_utils_op_sep_space.c
*/
int		is_operand(char *str);
int		is_separator(char c);
int		skip_spaces(char **str);
void	str_to_separator(char **str);
char	*strdup_and_inc_input(t_shell *shell, char **input);

/*
** env_utils.c
*/
void	ft_env_add_back(t_env **alst, t_env *new);
t_env	*ft_env_last(t_env *lst);
void	ft_print_env_var(t_env *var_end);
void	ft_env_remove_if(t_env **begin_list, void *name_ref,
		int (*cmp)());
void	ft_print_export_var(t_env *var_end);
void	ft_remove_elem(t_env **ptr_back, t_env **ptr);
void	ft_sort_export_var(t_env *env);
void	ft_swap_env(t_env *a, t_env *b);
t_env	*ft_clone_export_env(t_env *lst);
char	*ft_get_env_value(t_shell *shell, char *txt, int *j, int i);
char	*ft_search_env_content(t_shell *shell, char *name, int limit);
/*
** math.c
*/
int	ft_max(int a, int b);
int	ft_min(int a, int b);
int	ft_abs(int a);


/*
****************************************************
**					  COMMANDS					  **
****************************************************
*/
/*
** Commands
*/
int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env, int to_print);
int		ft_env(t_shell *shell, char **exec_args, char **tab_env, int to_print);
int		ft_cd(t_shell *shell, char **exec_args, char **tab_env, int to_print);
int		ft_unset(t_shell *shell, char **exec_args, char **tab_env, int to_print);
int		ft_echo(t_shell *shell, char **exec_args, char **tab_env, int to_print);
int		ft_export(t_shell *shell, t_tree *node);

void	ft_exit(t_shell *shell, char **exec_args, char **tab_env, int to_print);

/*
** Utils for commands
*/
int		ft_create_env_vars(t_shell *shell);
int		ft_fill_lst_env(t_shell *shell, char **envp);
char	*ft_fill_env_content(t_shell *shell, char *str);
int		ft_fill_tab_env(t_shell *shell, char **envp);
t_env	*ft_fill_first_lst(t_shell *shell, char **tab, t_env *lst);
int		get_var_env(t_shell *shell, char *var_name, char **content);
char	*ft_get_env_value(t_shell *shell, char *txt, int *j, int i);


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