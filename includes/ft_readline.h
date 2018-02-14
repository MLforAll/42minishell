/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/14 08:14:55 by kdumarai         ###   ########.fr       */
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
** ft_readline codes
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
** linked list for history mgmt
*/

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

/*
** Functions
*/

void			line_add(char **line, char *add, t_cursor *csr);
char			*ft_readline(const char *prompt, char **env, t_history *hist);

/*
** Utilities functions
*/

int				rl_csr_keys(char *buff, t_cursor *csr);
int				rl_history_keys(t_history **history, char *buff, char **line);
int				rl_add_text(char *buff, char *line, t_cursor *csr);
void			rl_rm_text(char *line, t_cursor *csr);

/*
** Autocompletion
*/

void			ac_line(char **line, t_cursor *csr, const char *pr, char **env);

/*
** History
*/

t_history		*ft_histnew(char *line);
void			ft_histadd(t_history **headref, char *line);
void			ft_histdelone(t_history	**hist);
void			ft_histdel(t_history **headref);

/*
** Autocompletion Utilities functions
*/

t_list			*get_ac_result(char *line, char *region, char **env);

#endif
