/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 21:36:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "msh_data.h"

t_cmd	*get_cmd_list(char *line);
char	*ft_readline(const char *prompt);

int		exec_cmd(t_cmd *cmd);
char	*search_dir_for_exec(const char *path, const char *name);

t_cmd	*ft_cmdnew(void);
void	ft_cmdpb(t_cmd **headref, t_cmd *new);

#endif