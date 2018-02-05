/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocompletion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/03 21:51:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ft_readline.h"
#include "minishell.h"

static t_list	*get_res_with_path(char *base, char **env)
{
	char	*pathenv;
	char	**paths;
	char	**bw;
	t_list	*ret;
	t_list	*new;

	if (!base || !*base || !(pathenv = get_env_var(env, "PATH")))
		return (NULL);
	paths = ft_strsplit(pathenv, ':');
	bw = paths;
	ret = NULL;
	while (*bw)
	{
		if ((new = search_files_begin(base, *bw, TRUE)))
			ft_lstadd(&ret, new);
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
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		new = 0;
		new = ft_strcmpi(lst->content, lst->next->content);
		len = (new < len || first) ? new : len;
		if (first)
			first = FALSE;
		lst = lst->next;
	}
	return (len == 0 ? NULL : ft_strsub(lst->content, 0, len));
}

static int		check_is_command(char *line)
{
	size_t	nchars;

	nchars = 0;
	while (*line)
	{
		if (*line == ' ' && nchars > 0)
			return (0);
		nchars += (*line > 32 && *line < 127);
		line++;
	}
	return (1);
}

static void		show_choices(t_list **res, const char *prompt, char *line)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	ft_lstmergesort(res, &ft_lstsortalpha, NO);
	ft_putlst_fd(*res, STDIN_FILENO);
	ft_putstr_fd(prompt, STDIN_FILENO);
	ft_putstr_fd(line, STDIN_FILENO);
}

void			ac_line(char **line, t_cursor *csr, const char *pr, char **env)
{
	char	*last;
	t_list	*res;
	char	*fname;
	char	*diff;
	char	*base;

	last = get_last_component(*line, ' ');
	fname = get_name_from_path(last);
	res = (!ft_strchr(*line, '/') && check_is_command(*line)) \
								? get_res_with_path(last, env) \
								: search_files_begin(last, NULL, FALSE);
	base = (res && !res->next) ? res->content : get_highest_common(res);
	if (base && *(diff = ft_strdiff(base, fname)))
	{
		line_add(line, diff, csr);
		if (base == res->content)
			line_add(line, (res->content_size == DT_DIR) ? "/" : " ", csr);
	}
	else if (res)
		show_choices(&res, pr, *line);
	if (base && base != res->content)
		ft_strdel(&base);
	ft_lstdel(&res, &free_tlist);
}