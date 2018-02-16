/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 07:11:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/16 20:26:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_readline.h"

t_history	*ft_histnew(char *line)
{
	t_history	*ret;

	if (!(ret = (t_history*)malloc(sizeof(t_history))))
		return (NULL);
	ft_bzero(ret, sizeof(t_history));
	ret->line = ft_strdup(line);
	return (ret);
}

void		ft_histadd(t_history **headref, char *line)
{
	t_history	*new;
	t_history	*bak;

	if (!headref || !line || !(new = ft_histnew(line)))
		return ;
	bak = *headref;
	if (bak)
	{
		bak->prev = new;
		new->next = bak;
	}
	*headref = new;
}

void		ft_histdelone(t_history **hist)
{
	t_history	*bak;

	if (!hist || !*hist)
		return ;
	bak = (*hist)->next;
	free((*hist)->line);
	free(*hist);
	*hist = bak;
}

void		ft_histdel(t_history **headref)
{
	t_history	*bw;

	if (!headref)
		return ;
	bw = *headref;
	while (bw)
		ft_histdelone(&bw);
	*headref = NULL;
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
