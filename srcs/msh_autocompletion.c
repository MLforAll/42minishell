/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_autocompletion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 12:56:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_readline.h"
#include "minishell.h"

static char		*get_diff(char *base, char *check)
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

static void		rm_dups(t_list **lst)
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

static t_list	*get_res_with_path(char *base, char **env)
{
	char	**paths;
	char	**bw;
	t_list	*ret;
	t_list	**ptr;

	paths = ft_strsplit(get_env_var(env, "PATH"), ':');
	bw = paths;
	ret = NULL;
	ptr = &ret;
	while (*bw)
	{
		*ptr = search_execs_begin(base, *bw);
		if (*ptr)
			ptr = &(*ptr)->next;
		bw++;
	}
	rm_dups(&ret);
	ft_tabfree(&paths);
	return (ret);
}

void			ac_line(char **line, t_cursor *csr, const char *prmpt, char **env)
{
	char	*last;
	t_list	*res;
	char	*fname;
	char	*diff;

	last = (last = ft_strchr(*line, ' ')) ? last + 1 : *line;
	fname = (fname = ft_strrchr(last, '/')) ? fname + 1 : last;
	res = (!ft_strchr(*line, ' ') && !ft_strchr(*line, '/')) \
								? get_res_with_path(last, env) \
								: search_execs_begin(last, NULL);
	if (res && !res->next)
	{
		if ((diff = get_diff(res->content, fname)))
			line_add(line, diff, csr);
	}
	else if (res)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		ft_putlst_fd(res, STDIN_FILENO);
		ft_putstr_fd(prmpt, STDIN_FILENO);
		ft_putstr_fd(*line, STDIN_FILENO);
	}
	ft_lstdel(&res, &free_tlist);
}
