/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:10:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 20:01:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

typedef struct		s_cmd
{
	int				c_builtin;
	char			*c_path;
	char			**c_argv;
	int				c_prereq;
	int				c_outfd;
	int				c_errfd;
	struct s_cmd	*next;
}					t_cmd;

#endif