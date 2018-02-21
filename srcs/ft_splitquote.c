/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 02:37:36 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/21 00:53:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	is_c_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (TRUE);
		charset++;
	}
	return (FALSE);
}

static void	add_elem(t_list **dest, char **last, unsigned int *idx)
{
	t_list			*new;

	if (!dest || !last || !idx)
		return ;
	if (*idx > 0)
	{
		if (!(new = ft_lstnew(NULL, 0)))
			return ;
		if ((new->content = ft_strsub(*last, 0, *idx)))
			new->content_size = ft_strlen(new->content) + 1;
		ft_lstpush(dest, new);
	}
	*last = (*last) + *idx + 1;
	*idx = 0;
}

int			ft_splitquote(t_list **dest, char *s, char *charset, char qc)
{
	char			*last;
	unsigned int	idx;
	int				split;

	*dest = NULL;
	idx = 0;
	if (!(last = s))
		return (FALSE);
	split = TRUE;
	while (last[idx])
	{
		if (last[idx] == qc && (idx == 0 || last[idx - 1] != '\\'))
			split = !split;
		if (!last[idx] || (is_c_charset(last[idx], charset) && split))
			add_elem(dest, &last, &idx);
		else
			idx++;
	}
	if (!split)
	{
		ft_lstdel(dest, &free_tlist);
		return (FALSE);
	}
	add_elem(dest, &last, &idx);
	return (TRUE);
}
