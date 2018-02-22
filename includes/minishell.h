/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 04:42:24 by kdumarai         ###   ########.fr       */
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
# define SH_BLTNS			"echo\0cd\0exit\0env\0setenv\0unsetenv\0source\0"

# define SH_DEFAULT_PATH_1	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:"
# define SH_DEFAULT_PATH_2	"/opt/X11/bin"
# define SH_DEFAULT_PATH	SH_DEFAULT_PATH_1 SH_DEFAULT_PATH_2

/*
** cmd parsing
*/

char	*get_cmd_path(char *line_cmd, char **env);
int		ft_splitquote(t_list **dest, char *s, char *charset, char qc);
t_cmd	*interpret_cmd(char *cline, char **env);

/*
** cmd exec
*/

int		exec_shell(const char *path, char ***env);
int		exec_cmd(t_cmd *cmd, char ***env);
int		exec_cmds(char *line, char ***env);

/*
** builtins
*/

int		echo_bltn(int ac, char **av, char ***env, int outfd);
int		exit_bltn(int ac, char **av, char ***env, int outfd);

char	*getset_pwd_env(char ***env);
int		cd_bltn(int ac, char **av, char ***env, int outfd);

int		env_bltn(int ac, char **av, char ***env, int outfd);
int		setenv_bltn(int ac, char **av, char ***env, int outfd);
int		unsetenv_bltn(int ac, char **av, char ***env, int outfd);
int		source_bltn(int ac, char **av, char ***env, int outfd);

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
char	*chg_env_var(char **env, const char *var, char *new);
char	*set_env_var(char ***env, const char *var, char *value);
void	del_env_var(char ***env, const char *var);

char	*set_env_from_str(char ***env, char *str);
char	*set_env_var_n(char ***env, const char *var, int value);

/*
** piping
*/

void	dup_out_to_pipe(int outfd, int pfd);

/*
** misc functions / utilities
*/

char	*get_last_tabitem(char **tab);
char	*get_last_component(const char *str, char c);
char	*get_name_from_path(const char *path);
char	*get_name_from_path_2(const char *path);

int		free_return(void **data, int retv);
void	switch_signals(int ign);

/*
** errors
*/

int		msh_err(int errc, const char *bltn, const char *path);
int		msh_err_ret(int errc, const char *bltn, const char *path, int retv);
void	msh_child_sighandler(int sigc);
int		get_errcode_for_path(const char *path, int mode, int dir);

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
