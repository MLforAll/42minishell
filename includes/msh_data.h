/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/07 06:09:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

/*
** cmd struct
**
** NOTE, 03/02/18:
**	c_prereq, c_outs
**	are UNUSED!
*/

typedef struct		s_cmd
{
	int				(*builtin)(int, char **, char ***);
	char			*c_path;
	char			**c_argv;
	int				c_prereq;
	char			**c_outs;
	struct s_cmd	*next;
}					t_cmd;

#endif
