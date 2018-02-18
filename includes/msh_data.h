/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/18 08:03:30 by kdumarai         ###   ########.fr       */
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
	int				(*builtin)(int, char **, char ***, int outfd);
	char			*c_path;
	char			**c_argv;
	int				c_prereq;
	int				c_pfd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

#endif
