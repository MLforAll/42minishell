/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_autocompletion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:47:05 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_readline.h"
#include "minishell.h"

static char	*get_diff(char *base, char *check)
{
	if (!base || !check)
		return (NULL);
	while (*base && *check && *base == *check)
	{
		base++;
		check++;
	}
	return (base);
}

void		autocomplete_line(char **line, t_cursor *csr)
{
	char	**comps;
	size_t	len;
	t_list	*res;
	char	*fname;
	char	*diff;

	comps = ft_strsplit(*line, ' ');
	len = ft_tablen((const char**)comps);
	fname = ft_strrchr(comps[len - 1], '/');
	fname = (fname == NULL) ? comps[len - 1] : fname + 1;
	res = search_execs_begin(comps[len - 1], (len == 1) ? "/usr/bin" : NULL);
	if (res && !res->next)
	{
		if ((diff = get_diff(res->content, fname)))
			line_add(line, diff, csr);
	}
	/*else if (res)
	{
		ft_putchar('\n');
		ft_putlst(res);
	}*/
	ft_lstdel(&res, &free_tlist);
	ft_tabfree(&comps);
}
