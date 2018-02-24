/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_csrkeys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/24 01:04:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

static void	configure_rightk(char *buff, t_readline *rl)
{
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return ;
	if ((rl->csr.pos + rl->prlen) % ws.ws_col == 0)
	{
		ft_putstr_fd("\033[", STDIN_FILENO);
		ft_putnbr_fd(ws.ws_col, STDIN_FILENO);
		ft_putchar_fd('D', STDIN_FILENO);
		ft_putstr_fd("\033[B", STDIN_FILENO);
	}
	else
		ft_putstr_fd(buff, STDIN_FILENO);
}

int			rl_csr_keys(char *buff, t_readline *rl)
{
	int				ret;
	int				keys[2];

	keys[0] = (ft_strcmp(ESC_RIGHTK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_LEFTK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	ret = -1;
	if (keys[0] && rl->csr.pos < rl->csr.max)
	{
		rl->csr.pos++;
		configure_rightk(buff, rl);
		ret = 1;
	}
	if (keys[1] && rl->csr.pos > 0)
	{
		rl->csr.pos--;
		ft_putstr_fd(buff, STDIN_FILENO);
		ret = 1;
	}
	return (ret);
}

static void	configure_hekeys(int k[2], size_t *len, char *ckey, t_readline *rl)
{
	struct winsize	ws;

	if (!k || !len || !ckey || !rl)
		return ;
	if (k[0] && ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return ;
	if (k[0] && rl->csr.pos < rl->csr.max
		&& rl->csr.max + rl->prlen < ws.ws_col)
	{
		*len = rl->csr.max - rl->csr.pos;
		*ckey = 'C';
		rl->csr.pos = rl->csr.max;
	}
	else if (k[1] && rl->csr.pos > 0)
	{
		*len = rl->csr.pos;
		*ckey = 'D';
		rl->csr.pos = 0;
	}
}

int			rl_home_end_keys(char *buff, t_readline *rl)
{
	int				keys[2];
	size_t			len;
	char			ckey;

	keys[0] = (ft_strcmp(ESC_ENDK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_HOMEK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	len = 0;
	configure_hekeys(keys, &len, &ckey, rl);
	if (len == 0)
		return (-1);
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(len, STDIN_FILENO);
	ft_putchar_fd(ckey, STDIN_FILENO);
	return (1);
}
