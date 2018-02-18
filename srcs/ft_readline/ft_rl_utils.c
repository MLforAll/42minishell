/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/18 04:19:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "libft.h"
#include "ft_readline.h"

int		rl_set_term(int fd, int echo, const char *prompt)
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

int		rl_csr_keys(char *buff, t_cursor *csr)
{
	int		ret;
	int		keys[2];

	keys[0] = (ft_strcmp(ESC_RIGHTK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_LEFTK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	ret = -1;
	if (keys[0] && csr->pos < csr->max)
	{
		csr->pos++;
		ret = 1;
	}
	if (keys[1] && csr->pos > 0)
	{
		csr->pos--;
		ret = 1;
	}
	if (ret == 1)
		ft_putstr_fd(buff, STDIN_FILENO);
	return (ret);
}

int		rl_home_end_keys(char *buff, t_cursor *csr)
{
	int		keys[2];
	size_t	len;
	char	*ckey;
	char	*seq;

	keys[0] = (ft_strcmp(ESC_ENDK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_HOMEK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	len = 0;
	if (keys[0] && csr->pos < csr->max)
	{
		len = csr->max - csr->pos;
		ckey = ESC_RIGHTK;
		csr->pos = csr->max;
	}
	else if (keys[1] && csr->pos > 0)
	{
		len = csr->pos;
		ckey = ESC_LEFTK;
		csr->pos = 0;
	}
	if (len == 0 || !(seq = ft_strnew(len * ft_strlen(ckey))))
		return (-1);
	while (len--)
		ft_strcat(seq, ckey);
	ft_putstr_fd(seq, STDIN_FILENO);
	free(seq);
	return (1);
}

void	rl_line_rm(char **line, size_t len, t_cursor *csr)
{
	char			*tmp;
	size_t			rpt;

	if (!line || !len || !csr)
		return ;
	rpt = len;
	while (rpt--)
	{
		ft_putstr_fd(ESC_LEFTK, STDIN_FILENO);
		csr->pos--;
	}
	ft_putstr_fd("\033[K\033[s", STDIN_FILENO);
	if (csr->pos + len < csr->max)
		ft_putstr_fd(*line + csr->pos + len, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	tmp = *line;
	*line = ft_strsub(tmp, 0, csr->pos);
	if (csr->pos + len < csr->max)
		ft_stradd(line, tmp + csr->pos + len);
	free(tmp);
	rpt = len;
	while (rpt--)
		csr->max--;
}

void	rl_line_add(char **line, char *add, t_cursor *csr)
{
	char	*tmp;
	size_t	len;

	if (!line || !add || !csr || !(len = ft_strlen(add)))
		return ;
	ft_putstr_fd("\033[K", STDIN_FILENO);
	ft_putstr_fd(add, STDIN_FILENO);
	if (csr->pos < csr->max)
	{
		ft_putstr_fd("\033[s", STDIN_FILENO);
		ft_putstr_fd(*line + csr->pos, STDIN_FILENO);
		ft_putstr_fd("\033[u", STDIN_FILENO);
	}
	tmp = *line;
	*line = ft_strsub(tmp, 0, csr->pos);
	ft_stradd(line, add);
	if (csr->pos < csr->max)
		ft_stradd(line, tmp + csr->pos);
	free(tmp);
	csr->max += len;
	csr->pos += len;
}
