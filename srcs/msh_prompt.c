/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/16 18:58:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include <pwd.h>
#include <stdlib.h>
#include "minishell.h"

static void	add_username(char **dest)
{
	uid_t			puid;
	struct passwd	*ppw;

	puid = getuid();
	if (!(ppw = getpwuid(puid)))
		return ;
	ft_stradd(dest, ppw->pw_name);
}

static void	add_hostname(char **dest)
{
	char			hostname[MAXHOSTNAMELEN + 1];
	char			*dot;

	if (gethostname(hostname, MAXHOSTNAMELEN) == -1)
		return ;
	if ((dot = ft_strchr(hostname, '.')))
		ft_strnadd(dest, hostname, dot - hostname);
	else
		ft_stradd(dest, hostname);
}

static void	add_pwd(char **dest, int all, char **env)
{
	char			*path;
	char			*pwd;
	char			*home;
	char			*tmp;

	tmp = NULL;
	if (!(pwd = get_env_var(env, "PWD")))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return ;
		path = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		home = get_env_var(env, "HOME");
		path = ft_strdup((pwd && home && !ft_strcmp(pwd, home)) ? "~" : pwd);
	}
	if (!all)
	{
		free(path);
		path = get_name_from_path_2(path);
	}
	ft_stradd(dest, path);
	free(path);
}

char		*get_prompt_from_str(char *s, char **env)
{
	char			*ret;
	char			*af;

	ret = ft_strnew(0);
	while (*s)
	{
		if ((af = ft_strstart(s, "\\u")))
			add_username(&ret);
		else if ((af = ft_strstart(s, "\\h")))
			add_hostname(&ret);
		else if ((af = ft_strstart(s, "\\w")))
			add_pwd(&ret, YES, env);
		else if ((af = ft_strstart(s, "\\W")))
			add_pwd(&ret, NO, env);
		else if ((af = ft_strstart(s, "\\033")))
			ft_stradd(&ret, "\033");
		else
		{
			af = s + 1;
			ft_strnadd(&ret, s, 1);
		}
		s += (af - s);
	}
	return (ret);
}
