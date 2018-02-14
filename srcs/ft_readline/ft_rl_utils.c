/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/14 08:14:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

int			rl_csr_keys(char *buff, t_cursor *csr)
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

int			rl_history_keys(t_history **history, char *buff, char **line)
{
	int		ret;

	if (!*history)
		return (FALSE);
	ret = FALSE;
	if (ft_strcmp("\033[A", buff) == 0 && (*history)->next)
	{
		*history = (*history)->next;
		ret = TRUE;
	}
	if (ft_strcmp("\033[B", buff) == 0 && (*history)->prev)
	{
		*history = (*history)->prev;
		ret = TRUE;
	}
	if (!ret)
		return (FALSE);
	free(*line);
	*line = ft_strdup((*history)->line);
	return (TRUE);
}

static int	rl_add_char(char c, t_cursor *csr)
{
	if (!ft_isprint(c))
		return (FALSE);
	ft_putchar_fd(c, STDIN_FILENO);
	csr->max++;
	csr->pos++;
	return (TRUE);
}

int			rl_add_text(char *buff, char *line, t_cursor *csr)
{
	int		ret;

	ret = 0;
	if (*buff == 27)
		return (0);
	ft_putstr_fd("\033[K", STDIN_FILENO);
	while (*buff)
		ret += rl_add_char(*(buff++), csr);
	ft_putstr_fd("\033[s", STDIN_FILENO);
	if (csr->pos < csr->max)
		ft_putstr_fd(line + csr->pos, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	return (ret);
}

void		rl_rm_text(char *line, t_cursor *csr)
{
	ft_putstr_fd("\033[D\033[K\033[s", STDIN_FILENO);
	ft_putstr_fd(line + csr->pos, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	csr->max--;
	csr->pos--;
}
