/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/11 08:50:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "msh_data.h"
# include "msh_prompt.h"

/*
** macros
*/

# define SH_NAME			"msh"
# define SH_PLAIN_PROMPT	"msh$ "
# define SH_RC				".mshrc"
# define SH_BLTNS			"echo\0cd\0exit\0env\0setenv\0unsetenv\0"

# define SH_ERR_UNDEFINED	0
# define SH_ERR_NOCMD		1
# define SH_ERR_NOENT		2
# define SH_ERR_NOCD		3
# define SH_ERR_NOSET		4
# define SH_ERR_TMARG		5
# define SH_ERR_PERM		6

/*
** cmd parsing and exec
*/

int		exec_shell(const char *path, char ***env);

int		exec_cmds(char *line, char ***env);
int		exec_cmd(t_cmd *cmd, char ***env);

char	*get_cmd_path(char *line_cmd, char **env);
t_cmd	*interpret_cmd(char *cline, char **env);

/*
** builtins
*/

int		echo_bltn(int ac, char **av, char ***env);
int		cd_bltn(int ac, char **av, char ***env);
int		exit_bltn(int ac, char **av, char ***env);

int		env_bltn(int ac, char **av, char ***env);
int		setenv_bltn(int ac, char **av, char ***env);
int		unsetenv_bltn(int ac, char **av, char ***env);

/*
** fsexp utilities
*/

char	*get_basedir(const char *f_path);
char	*search_dir_for_file(const char *d_path, const char *name);
t_list	*search_files_begin(const char *f_path, const char *s_dir, int exec);

/*
** env mgmt
*/

char	*get_env_var(char **env, const char *var);
void	set_env_var(char ***env, const char *var, char *value);
void	set_env_from_str(char ***env, char *str);
void	del_env_var(char ***env, const char *var);

/*
** misc functions / utilities
*/

char	*ft_strdiff(char *base, char *check);
char	*get_last_component(const char *str, char c);
char	*get_name_from_path(const char *path);
char	*get_name_from_path_2(const char *path);

int		msh_err(int errc, const char *bltn, const char *path);
int		msh_err_ret(int errc, const char *bltn, const char *path, int retv);
void	msh_child_sighandler(int sigc);

/*
** lists
*/

t_cmd	*ft_cmdnew(void);
void	ft_cmdpush(t_cmd **headref, t_cmd *new);
void	ft_cmddel(t_cmd **headref);
void	ft_cmddelone(t_cmd **cmdref);

void	free_tlist(void *content, size_t size);
void	ft_lstrmdups(t_list **lst);
int		ft_lstsortalpha(t_list *a, t_list *b);

#endif
