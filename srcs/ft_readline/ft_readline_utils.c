/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 20:14:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_readline.h"

int		is_buff_text(char *buff)
{
	int		chks[4];

	chks[0] = ft_isprint(buff[0]);
	chks[1] = ft_isprint(buff[1]) || buff[1] == 0;
	chks[2] = ft_isprint(buff[2]) || buff[2] == 0;
	chks[3] = ft_isprint(buff[3]) || buff[3] == 0;
	return (chks[0] && chks[1] && chks[2] && chks[3]);
}

int		rl_csr_keys(char *buff, t_cursor *csr)
{
	int		ret;

	ret = FALSE;
	if (ft_strcmp("\033[C", buff) == 0 && csr->pos < csr->max)
	{
		csr->pos++;
		ret = TRUE;
	}
	if (ft_strcmp("\033[D", buff) == 0 && csr->pos > 0)
	{
		csr->pos--;
		ret = TRUE;
	}
	if (ret)
		ft_putstr_fd(buff, STDIN_FILENO);
	return (ret);
}

void	rl_add_text(char *buff, ssize_t len, char *line, t_cursor *csr)
{
	ft_putstr_fd("\033[K", STDIN_FILENO);
	ft_putstr_fd(buff, STDIN_FILENO);
	ft_putstr_fd("\033[s", STDIN_FILENO);
	ft_putstr_fd(line + csr->pos, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	csr->max += len;
	csr->pos += len;
}

void	rl_rm_text(char *line, t_cursor *csr)
{
	ft_putstr_fd("\033[D\033[K\033[s", STDIN_FILENO);
	ft_putstr_fd(line + csr->pos, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	csr->max--;
	csr->pos--;
}
