/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/24 17:22:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "minishell.h"

/*
** ft_readline
** a smaller copy of GNU's readline function, used by shells like bash
** that allows line-editing
**
** To accomplish that, the terminal is set in raw mode, so a read
** call on stdin will respond at each keypress
*/

static void	set_noecho(int fd, struct termios t)
{
	t.c_lflag &= ~(ICANON | ECHO | ISIG);
	tcsetattr(fd, TCSANOW, &t);
}

static int	act_char(char *buff, ssize_t len)
{
	char			c;

	c = (len == 1) ? *buff : 0;
	//print_nums_debug(buff);
	if (ft_isprint(c))
		return (1);
	if (c == '\n' || c == 3)
		return (-1);
	if (c == 4)
		return (-2);
	if (c == 127)
	{
		ft_putstr("\033[D\033[K");
		return (3);
	}
	if (ft_strcmp("\033[D", buff) == 0 || ft_strcmp("\033[C", buff) == 0)
		return (2);
	return (0);
}

static void	mod_line(char **line, char *buff, int act_ret)
{
	size_t			len;
	char			*tmp;

	tmp = *line;
	if (act_ret == 3)
	{
		len = ft_strlen(*line);
		if (!len)
			return ;
		*line = (char*)malloc(sizeof(char) * len);
		ft_strncpy(*line, tmp, len - 1);
		(*line)[len - 1] = '\0';
	}
	else
		*line = ft_strnjoin(*line, buff, 1);
	free(tmp);
}

char		*ft_readline(const char *prompt)
{
	char			buff[5];
	ssize_t			rb;
	int				act_ret;
	char			*ret;
	struct termios	t;

	ft_putstr(prompt);
	ret = ft_strnew(0);
	tcgetattr(STDOUT_FILENO, &t);
	set_noecho(STDOUT_FILENO, t);
	while ((rb = read(STDIN_FILENO, buff, 4)) > 0)
	{
		buff[rb] = '\0';
		if ((act_ret = act_char(buff, rb)) > 0 && act_ret < 3)
			ft_putstr(buff);
		if (act_ret < 0)
		{
			ft_putchar('\n');
			break ;
		}
		else if (act_ret != 2 && act_ret != 0)
			mod_line(&ret, buff, act_ret);
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &t);
	if (act_ret == -2)
		ft_strdel(&ret);
	return (ret);
}
