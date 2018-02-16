/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/16 22:03:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

/*
** ft_readline
** a smaller copy of GNU's readline function, used by shells like bash
** that allows line-editing.
**
** To accomplish that, the terminal is set in raw mode, so a read
** call on stdin will respond at each keypress.
*/

static int	rl_add_text(char *buff, char **line, t_cursor *csr)
{
	char			add[5];
	unsigned int	idx;

	if (*buff == 27)
		return (0);
	idx = 0;
	ft_bzero(add, sizeof(add));
	while (*buff)
	{
		if (ft_isprint(*buff))
		{
			add[idx] = *buff;
			idx++;
		}
		buff++;
	}
	rl_line_add(line, add, csr);
	return ((idx > 0));
}

static int	rl_rm_text(char **line, char *buff, t_cursor *csr)
{
	if (*buff == 127 && csr->pos > 0)
	{
		rl_line_rm(line, 1, csr);
		return (TRUE);
	}
	return (FALSE);
}

static void	act_on_buff(char *buff, char **line, const char *pr, t_cursor *csr)
{
	if (rl_add_text(buff, line, csr))
		return ;
	if (rl_rm_text(line, buff, csr))
		return ;
	if (rl_csr_keys(buff, csr))
		return ;
	if (*buff == 4 || *buff == 3 || *buff == 21)
		ft_strdel(line);
	if (*buff == 3 || *buff == 21)
		*line = ft_strnew(0);
	if (*buff == 21)
	{
		ft_putstr_fd("\r\033[K", STDIN_FILENO);
		ft_putstr_fd(pr, STDIN_FILENO);
		return ;
	}
	if (*buff == 4 || *buff == 3)
		return ;
	//ft_putchar_fd('\a', STDIN_FILENO);
}

char		*ft_readline(const char *prompt, char **env, t_history *hist)
{
	char			buff[5];
	t_cursor		csr;
	char			*ret;

	if (!rl_set_term(STDIN_FILENO, NO, prompt))
		return (NULL);
	ft_bzero(&csr, sizeof(t_cursor));
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while (read(STDIN_FILENO, buff, 4))
	{
		act_on_buff(buff, &ret, prompt, &csr);
		if (rl_history_keys(&hist, buff, &ret))
		{
			ft_putstr_fd("\r\033[K", STDIN_FILENO);
			ft_putstr_fd(prompt, STDIN_FILENO);
			ft_putstr_fd(ret, STDIN_FILENO);
			csr.max = ft_strlen(ret);
			csr.pos = csr.max;
		}
		if (*buff == '\t')
			ac_line(&ret, &csr, prompt, env);
		if (*buff == '\n' || *buff == 4 || *buff == 3)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			break ;
		}
		ft_bzero(buff, sizeof(buff));
	}
	rl_set_term(STDIN_FILENO, YES, prompt);
	return (ret);
}
