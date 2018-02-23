/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 23:02:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
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

static void	act_keys(char **line, char *buff, char **env, t_readline *rl)
{
	int					rval;
	unsigned int		idx;
	static int			(*f[])(char *, t_cursor *) =
	{&rl_csr_keys, &rl_home_end_keys, NULL};

	if ((rval = rl_history_keys(&rl->hist, buff, line)) > 0 && *line)
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
	int					retval;

	if (rl_input_add_text(buff, line, &rl->csr))
		return ;
	if ((retval = rl_input_rm_text(line, buff, &rl->csr)) == 1)
		return ;
	else if (retval == -1)
		ft_putchar_fd('\a', STDIN_FILENO);
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

static void	print_end_newlines(char *line, const char *prompt)
{
	struct winsize		ws;
	size_t				times;
	char				*buff;

	if (!line || !prompt)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return ;
	}
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return ;
	times = (ft_strlen(line) + ft_strlen(prompt)) / ws.ws_col;
	times += (times == 0);
	if (!(buff = (char*)malloc(sizeof(char) * (times + 1))))
		return ;
	ft_memset(buff, '\n', times);
	buff[times] = '\0';
	ft_putstr_fd(buff, STDIN_FILENO);
	free(buff);
}

char		*ft_readline(const char *prompt, char **env, t_history *hist)
{
	char				buff[5];
	t_readline			rl;
	char				*ret;

	if (!rl_set_term(STDIN_FILENO, NO, prompt))
		return (NULL);
	ft_bzero(&rl.csr, sizeof(t_cursor));
	rl.hist = hist;
	rl.prompt = prompt;
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while (ret && read(STDIN_FILENO, buff, 4) > 0)
	{
		act_keys(&ret, buff, env, &rl);
		act_on_buff(buff, &ret, &rl);
		if (*buff == '\n' || *buff == 4 || *buff == 3)
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	print_end_newlines(ret, prompt);
	rl_set_term(STDIN_FILENO, YES, prompt);
	return (ret);
}
