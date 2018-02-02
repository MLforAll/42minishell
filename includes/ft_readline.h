/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 20:14:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <string.h>
# include "libft.h"

/*
** BUFF_SIZE of ft_readline
** 25/01/18: to be used later
*/

# define RL_BUFF_SIZE		32

/*
** to fill later
*/

# define RL_BACKSPACE_ACT	4
# define RL_ADD_ACT			3
# define RL_DEFAULT_ACT		0
# define RL_MOVE_ACT		2
# define RL_QUIT_ACT		-1

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

void	ac_line(char **line, t_cursor *csr, const char *prmpt, char **env);
void	line_add(char **line, char *add, t_cursor *csr);
char	*ft_readline(const char *prompt, char **env);

/*
**
*/

int		is_buff_text(char *buff);
int		rl_csr_keys(char *buff, t_cursor *csr);
void	rl_add_text(char *buff, ssize_t len, char *line, t_cursor *csr);
void	rl_rm_text(char *line, t_cursor *csr);

#endif