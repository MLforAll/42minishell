/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/01 22:24:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "msh_data.h"

# define YES			1
# define NO				0
# define TRUE			1
# define FALSE			0

# define MSH_ERR_NOCMD	1
# define MSH_ERR_NOENT	2
# define MSH_ERR_NOCD	3
# define MSH_ERR_NOSET	4
# define MSH_ERR_TMARG	5
# define MSH_ERR_PERM	6

int		echo_bltn(int ac, char **av, char ***env);
int		cd_bltn(int ac, char **av, char ***env);
int		exit_bltn(int ac, char **av, char ***env);

int		env_bltn(int ac, char **av, char ***env);
int		setenv_bltn(int ac, char **av, char ***env);
int		unsetenv_bltn(int ac, char **av, char ***env);

int		exec_cmds(t_cmd *allcmds, char ***env);
int		exec_cmd(t_cmd *cmd, char ***env);

int		msh_err(int errc, const char *bltn, const char *path);

char	*ft_strdiff(char *base, char *check);
char	*get_last_component(const char *str, char c);
char	*get_name_from_path(const char *path);

char	*get_cmd_path(char *line_cmd, char **env);
t_cmd	*get_cmd_list(char *line, char **env);

char	*get_basedir(const char *path);
char	*search_dir_for_exec(const char *path, const char *name);
t_list	*search_execs_begin(const char *path, const char *search_dir);

char	*get_env_var(char **env, const char *var);
void	set_env_var(char ***env, const char *var, char *value);
void	set_env_from_str(char ***env, char *str);
void	del_env_var(char ***env, const char *var);

/*
** lists
*/

t_cmd	*ft_cmdnew(void);
void	ft_cmdpb(t_cmd **headref, t_cmd *new);
void	ft_cmddel(t_cmd **headref);
void	ft_cmddelone(t_cmd **cmdref);

void	free_tlist(void *content, size_t size);
void	ft_lstrmdups(t_list **lst);
int		ft_lstsortalpha(t_list *a, t_list *b);

#endif
