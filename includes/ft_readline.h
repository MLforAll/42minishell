/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 17:49:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

/*
** BUFF_SIZE of ft_readline
** 25/01/18: to be used later
*/

# define BUFF_SIZE	32

/*
** struct for cursor mgmt
*/

typedef struct	s_cursor
{
	size_t	pos;
	size_t	max;
}				t_cursor;

#endif