/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 21:55:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 22:21:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	free_tlist(void *content, size_t size)
{
	(void)size;
	free(content);
}

void	ft_lstrmdups(t_list **lst)
{
	t_list	*bw;
	t_list	*prev;
	t_list	*chk;
	t_list	**ptr;

	bw = *lst;
	prev = NULL;
	while (bw)
	{
		chk = *lst;
		while (chk != bw)
		{
			if (ft_strcmp(bw->content, chk->content) == 0)
			{
				ptr = (!prev) ? lst : &prev->next;
				*ptr = bw->next;
				ft_lstdelone(&bw, &free_tlist);
				bw = prev;
			}
			else
				chk = chk->next;
		}
		prev = bw;
		bw = bw->next;
	}
}
