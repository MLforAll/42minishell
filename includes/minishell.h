/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:37:13 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "msh_data.h"

# define YES	1
# define NO		0
# define TRUE	1
# define FALSE	0

int		echo_bltn(int ac, char **av, char ***env);
int		cd_bltn(int ac, char **av, char ***env);
int		exit_bltn(int ac, char **av, char ***env);

int		env_bltn(int ac, char **av, char ***env);
int		setenv_bltn(int ac, char **av, char ***env);
int		unsetenv_bltn(int ac, char **av, char ***env);

int		exec_cmds(t_cmd *allcmds, char ***env);
int		exec_cmd(t_cmd *cmd, char ***env);

void	msh_err(int errc, const char *bltn, const char *path);

t_cmd	*get_cmd_list(char *line, char **env);

char	*get_basedir(const char *path);
char	*search_dir_for_exec(const char *path, const char *name);
t_list	*search_execs_begin(const char *path, const char *search_dir);

char	*get_env_var(char **env, const char *var);
void	chg_env_var(char **env, const char *var, char *new);
void	add_env_var(char ***env, const char *var, char *value);
void	del_env_var(char ***env, const char *var);

t_cmd	*ft_cmdnew(void);
void	ft_cmdpb(t_cmd **headref, t_cmd *new);
void	ft_cmddel(t_cmd **headref);
void	ft_cmddelone(t_cmd **cmdref);
void	free_tlist(void *content, size_t size);

#endif
