/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_autocompletion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 22:20:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
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
	ft_lstrmdups(&ret);
	ft_tabfree(&paths);
	return (ret);
}

static char		*get_highest_common(t_list *lst)
{
	int		first;
	size_t	len;
	size_t	new;

	first = TRUE;
	len = 0;
	while (lst->next)
	{
		new = 0;
		new = ft_strcmpi((const char*)lst->content, (const char*)lst->next->content);
		len = (new < len || first) ? new : len;
		if (first)
			first = FALSE;
		lst = lst->next;
	}
	return (len == 0 ? NULL : ft_strsub(lst->content, 0, len));
}

void			ac_line(char **line, t_cursor *csr, const char *prmpt, char **env)
{
	char	*last;
	t_list	*res;
	char	*fname;
	char	*diff;
	char	*base;

	last = (last = ft_strrchr(*line, ' ')) ? last + 1 : *line;
	fname = (fname = ft_strrchr(last, '/')) ? fname + 1 : last;
	res = (!ft_strchr(*line, ' ') && !ft_strchr(*line, '/')) \
								? get_res_with_path(last, env) \
								: search_execs_begin(last, NULL);
	base = (res && !res->next) ? res->content : get_highest_common(res);
	if (base)
	{
		if ((diff = get_diff(base, fname)))
			line_add(line, diff, csr);
		if (base == res->content)
			line_add(line, (res->content_size == DT_DIR) ? "/" : " ", csr);
	}
	else if (res)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		ft_putlst_fd(res, STDIN_FILENO);
		ft_putstr_fd(prmpt, STDIN_FILENO);
		ft_putstr_fd(*line, STDIN_FILENO);
	}
	if (base && base != res->content)
		ft_strdel(&base);
	ft_lstdel(&res, &free_tlist);
}
