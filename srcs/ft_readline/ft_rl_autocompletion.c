/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocompletion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/09 07:47:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ft_readline.h"
#include "minishell.h"

static void		add_bltn_ac(char *base, t_list **res)
{
	char	*nptr;

	nptr = SH_BLTNS;
	while (*nptr)
	{
		if (ft_strstart(nptr, base))
			break ;
		nptr += ft_strlen(nptr) + 1;
	}
	if (*nptr)
		ft_lstadd(res, ft_lstnew(nptr, ft_strlen(nptr) + 1));
}

t_list			*get_res_with_path(char *base, char **env)
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
	add_bltn_ac(base, &ret);
	ft_lstrmdups(&ret);
	ft_tabfree(&paths);
	return (ret);
}
