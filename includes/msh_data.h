/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/09 08:05:48 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

/*
** cmd struct
**
** NOTE, 03/02/18:
**	c_prereq is unused!
*/

typedef struct		s_cmd
{
	int				(*builtin)(int, char **, char ***);
	char			*c_path;
	char			**c_argv;
	int				c_prereq;
	t_list			*redirs;
	int				*pfd;
	struct s_cmd	*next;
}					t_cmd;

#endif
