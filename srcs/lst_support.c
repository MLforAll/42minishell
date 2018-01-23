/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:49:11 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 20:05:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "msh_data.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*ret;

	ret = (t_cmd*)malloc(sizeof(t_cmd));
	ft_bzero(ret, sizeof(t_cmd));
	return (ret);
}

void	ft_cmdpb(t_cmd **headref, t_cmd *new)
{
	t_cmd	**tmp;

	if (!headref)
		return ;
	tmp = headref;
	while (*tmp)
		tmp = &(*tmp)->next;
	*tmp = new;
}

void	ft_cmddel(t_cmd **headref)
{
	t_cmd	*next;

	while (*headref)
	{
		next = *headref;
		if ((*headref)->c_argv)
			ft_tabfree(&(*headref)->c_argv);
		free(*headref);
		*headref = next;
	}
	*headref = NULL;
}
