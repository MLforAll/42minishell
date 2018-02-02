/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 20:15:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

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
		return (FALSE);
	if (!echo)
	{
		ft_putstr_fd(prompt, fd);
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
	}
	else
		t.c_lflag |= (ICANON | ECHO | ISIG);
	tcsetattr(fd, TCSANOW, &t);
	return (TRUE);
}

static int	act_char(char *buff, ssize_t len, char **line, t_cursor *csr)
{
	if (is_buff_text(buff))
	{
		rl_add_text(buff, len, *line, csr);
		return (RL_ADD_ACT);
	}
	if (*buff == 4 || *buff == 3)
		ft_strdel(line);
	if (*buff == 3)
		*line = ft_strnew(0);
	if (*buff == '\n' || *buff == 4 || *buff == 3)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return (RL_QUIT_ACT);
	}
	if (rl_csr_keys(buff, csr))
		return (RL_MOVE_ACT);
	if (*buff == 127 && csr->pos > 0)
	{
		rl_rm_text(*line, csr);
		return (RL_BACKSPACE_ACT);
	}
	return (RL_DEFAULT_ACT);
}

static void	mod_line(char **line, char *buff, int act_ret, t_cursor *csr)
{
	char			*tmp;

	tmp = *line;
	(void)act_ret;
	*line = ft_strnew(csr->max + 1);
	if (csr->pos > 0)
		ft_strncat(*line, tmp, csr->pos - (act_ret != 4));
	if (act_ret != 4)
		ft_strcat(*line, buff);
	if (csr->pos != csr->max)
		ft_strcat(*line, tmp + csr->pos + ((act_ret == 4) ? 1 : -1));
	(*line)[csr->max] = '\0';
	free(tmp);
}

void		line_add(char **line, char *add, t_cursor *csr)
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

	if (!set_term(STDIN_FILENO, FALSE, prompt))
		return (NULL);
	ft_bzero(&csr, sizeof(t_cursor));
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while ((rb = read(STDIN_FILENO, buff, 4)) > 0)
	{
		act_ret = act_char(buff, rb, &ret, &csr);
		if (*buff == '\t')
			ac_line(&ret, &csr, prompt, env);
		if (act_ret < 0)
			break ;
		else if (act_ret != 2 && act_ret != 0)
			mod_line(&ret, buff, act_ret, &csr);
		ft_bzero(buff, sizeof(buff));
	}
	set_term(STDIN_FILENO, 1, prompt);
	return (ret);
}
