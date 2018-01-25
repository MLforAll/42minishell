/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 21:37:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "msh_data.h"

int		echo_bltn(char **av);
int		exit_bltn(char **av);

int		exec_cmds(t_cmd *allcmds, char **env);
int		exec_cmd(t_cmd *cmd, char **env);

t_cmd	*get_cmd_list(char *line, char **env);
char	*ft_readline(const char *prompt);

char	*search_dir_for_exec(const char *path, const char *name);

char	*get_env_var(const char *var, char **env);
void	chg_env_var(const char *var, char *new, char **env);

t_cmd	*ft_cmdnew(void);
void	ft_cmdpb(t_cmd **headref, t_cmd *new);
void	ft_cmddel(t_cmd **headref);
void	ft_cmddelone(t_cmd **cmdref);

void		msh_err(int errc, const char *path);

#endif
