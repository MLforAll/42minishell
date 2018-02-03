/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/03 20:24:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

/*
** cmd struct
**
** NOTE, 03/02/18:
**	c_prereq, c_in, c_out, c_err
**	are UNUSED!
*/

typedef struct		s_cmd
{
	int				(*builtin)(int, char **, char ***);
	char			*c_path;
	char			**c_argv;
	int				c_prereq;
	char			*c_in;
	char			*c_out;
	char			*c_err;
	struct s_cmd	*next;
}					t_cmd;

#endif
