/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/18 08:54:18 by kdumarai         ###   ########.fr       */
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

static int	input_add_text(char *buff, char **line, t_cursor *csr)
{
	char				add[5];
	unsigned int		idx;

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

static int	input_rm_text(char **line, char *buff, t_cursor *csr)
{
	if (*buff == 127 && csr->pos > 0)
	{
		rl_line_rm(line, 1, csr);
		return (TRUE);
	}
	else if (ft_strcmp(buff, ESC_DELK) == 0 && csr->pos < csr->max)
	{
		ft_putstr_fd(ESC_RIGHTK, STDIN_FILENO);
		csr->pos++;
		rl_line_rm(line, 1, csr);
		return (TRUE);
	}
	return (FALSE);
}

static void	act_keys(char **line, char *buff, char **env, t_readline *rl)
{
	int					rval;
	unsigned int		idx;
	static int			(*f[])(char *, t_cursor *) =
	{&rl_csr_keys, &rl_home_end_keys, NULL};

	if ((rval = rl_history_keys(&rl->hist, buff, line)) > 0)
	{
		ft_putstr_fd("\r\033[K", STDIN_FILENO);
		ft_putstr_fd(rl->prompt, STDIN_FILENO);
		ft_putstr_fd(*line, STDIN_FILENO);
		rl->csr.max = ft_strlen(*line);
		rl->csr.pos = rl->csr.max;
	}
	else if (rval == -1)
		ft_putchar_fd('\a', STDIN_FILENO);
	idx = -1;
	while (f[++idx])
	{
		if ((rval = f[idx](buff, &rl->csr)) > 0)
			return ;
		else if (rval == -1)
			ft_putchar_fd('\a', STDIN_FILENO);
	}
	if (*buff == '\t')
		ac_line(line, &rl->csr, rl->prompt, env);
}

static void	act_on_buff(char *buff, char **line, t_readline *rl)
{
	if (input_add_text(buff, line, &rl->csr))
		return ;
	if (input_rm_text(line, buff, &rl->csr))
		return ;
	if (*buff == 4 || *buff == 3 || *buff == 21)
		ft_strdel(line);
	if (*buff == 3 || *buff == 21)
		*line = ft_strnew(0);
	if (*buff == 21)
	{
		ft_putstr_fd("\r\033[K", STDIN_FILENO);
		ft_putstr_fd(rl->prompt, STDIN_FILENO);
		ft_bzero(&rl->csr, sizeof(t_cursor));
		return ;
	}
	if (*buff == 4 || *buff == 3)
		return ;
}

char		*ft_readline(const char *prompt, char **env)
{
	char				buff[5];
	static t_history	*hist;
	t_readline			rl;
	char				*ret;

	if (!rl_set_term(STDIN_FILENO, NO, prompt))
		return (NULL);
	ft_bzero(&rl.csr, sizeof(t_cursor));
	rl.hist = hist;
	rl.prompt = prompt;
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while (read(STDIN_FILENO, buff, 4) > 0)
	{
		act_keys(&ret, buff, env, &rl);
		act_on_buff(buff, &ret, &rl);
		if (*buff == '\n' || *buff == 4 || *buff == 3)
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_set_term(STDIN_FILENO, YES, prompt);
	if (ret && *ret)
		ft_histadd(&hist, ret);
	return (ret);
}
