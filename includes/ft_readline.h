/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:03:05 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

/*
** BUFF_SIZE of ft_readline
** 25/01/18: to be used later
*/

# define RL_BUFF_SIZE	32

/*
** struct for cursor mgmt
*/

typedef struct	s_cursor
{
	unsigned int	pos;
	size_t			max;
}				t_cursor;

/*
** Functions
*/

void	autocomplete_line(char **line, t_cursor *csr);
void	line_add(char **line, char *add, t_cursor *csr);
char	*ft_readline(const char *prompt);

#endif