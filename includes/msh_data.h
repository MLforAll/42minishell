/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/23 16:10:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DATA_H
# define MSH_DATA_H

/*
** cmd struct
*/

typedef struct		s_cmd
{
	int				(*builtin)(int, char **, char ***, int outfd);
	char			*c_path;
	char			**c_argv;
	int				c_pfd[2];
	pid_t			c_pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

/*
** errs enum
*/

typedef enum		e_errs
{
	SH_ERR_UNDEFINED,
	SH_ERR_NOCMD,
	SH_ERR_NOENT,
	SH_ERR_NOCD,
	SH_ERR_NOSET,
	SH_ERR_TMARG,
	SH_ERR_PERM,
	SH_ERR_FORK,
	SH_ERR_TMLNK,
	SH_ERR_NOTDIR,
	SH_ERR_NUMARG,
	SH_ERR_INVID,
	SH_ERR_MAX
}					t_errs;

#endif
