/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 12:55:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "ft_readline.h"
#include "minishell.h"

/*
** ft_readline
** a smaller copy of GNU's readline function, used by shells like bash
** that allows line-editing
**
** To accomplish that, the terminal is set in raw mode, so a read
** call on stdin will respond at each keypress
*/

static int	set_term(int fd, int echo, const char *prompt)
{
	struct termios	t;

	if (tcgetattr(fd, &t))
		return (0);
	if (!echo)
	{
		ft_putstr_fd(prompt, fd);
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
	}
	else
		t.c_lflag |= (ICANON | ECHO | ISIG);
	tcsetattr(fd, TCSANOW, &t);
	return (1);
}

static int	act_char(char *buff, ssize_t len, char *line, t_cursor *csr)
{
	char			c;

	c = (len == 1) ? *buff : 0;
	//print_nums_debug(buff);
	if (ft_isprint(c))
	{
		ft_putstr_fd("\033[K", STDIN_FILENO);
		ft_putstr_fd(buff, STDIN_FILENO);
		ft_putstr_fd("\033[s", STDIN_FILENO);
		ft_putstr_fd(line + csr->pos, STDIN_FILENO);
		ft_putstr_fd("\033[u", STDIN_FILENO);
		csr->max++;
		csr->pos++;
		return (3);
	}

	if (c == '\n' || c == 3)
		return (-1);
	if (c == 4)
		return (-2);
	if (c == 127 && csr->pos > 0)
	{
		ft_putstr_fd("\033[D\033[K\033[s", STDIN_FILENO);
		ft_putstr_fd(line + csr->pos, STDIN_FILENO);
		ft_putstr_fd("\033[u", STDIN_FILENO);
		csr->max--;
		csr->pos--;
		return (4);
	}
	if (ft_strcmp("\033[C", buff) == 0 && csr->pos < csr->max)
	{
		csr->pos++;
		return (2);
	}
	if (ft_strcmp("\033[D", buff) == 0 && csr->pos > 0)
	{
		csr->pos--;
		return (2);
	}
	return (0);
}

static void	mod_line(char **line, char *buff, int act_ret, t_cursor *csr)
{
	char			*tmp;

	tmp = *line;
	(void)act_ret;
	//if (act_ret == 3)
	//{
		*line = ft_strnew(csr->max);
		if (csr->pos > 1)
			ft_strncat(*line, tmp, csr->pos);
		if (act_ret != 4)
			ft_strcat(*line, buff);
		ft_strcat(*line, tmp + csr->pos + (act_ret == 4 ? 1 : -1));
		//ft_strncpy(*line, tmp, csr->max - 1);
		(*line)[csr->max] = '\0';
	//}
	//else
	//	*line = ft_strnjoin(*line, buff, 1);
	free(tmp);
}

void	line_add(char **line, char *add, t_cursor *csr)
{
	char	*tmp;
	size_t	len;

	tmp = *line;
	*line = ft_strjoin(*line, add);
	free(tmp);
	len = ft_strlen(add);
	ft_putstr_fd(add, STDIN_FILENO);
	csr->max += len;
	csr->pos += len;
}

char		*ft_readline(const char *prompt, char **env)
{
	char			buff[5];
	ssize_t			rb;
	int				act_ret;
	t_cursor		csr;
	char			*ret;
	
	if (!set_term(STDIN_FILENO, 0, prompt))
		return (NULL);
	ft_bzero(&csr, sizeof(t_cursor));
	ret = ft_strnew(0);
	while ((rb = read(STDIN_FILENO, buff, 4)) > 0)
	{
		buff[rb] = '\0';
		if ((act_ret = act_char(buff, rb, ret, &csr)) > 0 && act_ret < 3)
			ft_putstr_fd(buff, STDIN_FILENO);
		if (*buff == '\t')
			ac_line(&ret, &csr, prompt, env);
		if (act_ret < 0)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			break ;
		}
		else if (act_ret != 2 && act_ret != 0)
			mod_line(&ret, buff, act_ret, &csr);
	}
	set_term(STDIN_FILENO, 1, prompt);
	if (act_ret == -2)
		ft_strdel(&ret);
	return (ret);
}
