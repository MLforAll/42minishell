/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/22 05:40:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "minishell.h"

static void	set_noecho(int fd, struct termios t)
{
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &t);
}

static int	act_char(char *buff, ssize_t len)
{
	char			c;

	c = (len == 1) ? *buff : 0;
	if (c >= 32 && c < 127)
		return (1);
	if (c == '\n')
		return (-1);
	if (c == 127)
		ft_putstr("\033[D\033[K");
	if (len == 3 && buff[0] == 27 && buff[1] == 91)
		ft_putstr((buff[2] == 68) ? "\033[D" : "\033[C");
	return (0);
}

static void	mod_line(char **line, char *buff)
{
	char			*tmp;

	tmp = *line;
	*line = ft_strnjoin(*line, buff, 1);
	free(tmp);
}

char		*readline(const char *header)
{
	char			buff[4];
	ssize_t			rb;
	int				act_ret;
	char			*ret;
	struct termios	t;

	ft_putstr(header);
	ret = ft_strnew(0);
	tcgetattr(STDOUT_FILENO, &t);
	set_noecho(STDOUT_FILENO, t);
	while ((rb = read(STDIN_FILENO, buff, 3)) > 0)
	{
		if ((act_ret = act_char(buff, rb)) == 1 || act_ret == -1)
			ft_putchar(*buff);
		if (act_ret == -1)
			break ;
		else
			mod_line(&ret, buff);
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &t);
	return (ret);
}
