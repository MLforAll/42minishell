/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:10:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 19:49:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

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
