/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/29 02:03:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include <pwd.h>
#include <stdlib.h>
#include "minishell.h"

int			add_username(char **dest)
{
	uid_t			puid;
	struct passwd	*ppw;

	if (!dest || !(puid = getuid()))
		return (FALSE);
	if (!(ppw = getpwuid(puid)))
		return (FALSE);
	ft_stradd(dest, ppw->pw_name);
	return (TRUE);
}

int			add_hostname(char **dest)
{
	char			hostname[MAXHOSTNAMELEN + 1];
	char			*dot;

	if (gethostname(hostname, MAXHOSTNAMELEN) == -1)
		return (FALSE);
	if ((dot = ft_strchr(hostname, '.')))
		ft_strnadd(dest, hostname, dot - hostname);
	else
		ft_stradd(dest, hostname);
	return (TRUE);
}

static char	*build_home(char *pwd, char **env)
{
	char			*ret;
	char			*home;
	const char		*stret;

	if (!pwd || !(home = get_env_var(env, "HOME")))
		return (NULL);
	if ((stret = ft_strstart(pwd, home)))
		ret = ft_strdup("~");
	else
		ret = ft_strnew(0);
	if (!ret)
		return (NULL);
	ft_stradd(&ret, (stret) ? stret : pwd);
	return (ret);
}

int			add_pwd(char **dest, int all, char **env)
{
	char			*path;
	char			*pwd;
	char			*tmp;

	tmp = NULL;
	if (!(pwd = get_env_var(env, "PWD")))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return (FALSE);
		path = tmp;
	}
	else
	{
		if (!(path = build_home(pwd, env)))
			return (FALSE);
	}
	if (!all)
	{
		tmp = path;
		path = get_name_from_path_2(path);
		ft_strdel(&tmp);
	}
	ft_stradd(dest, path);
	ft_strdel(&path);
	return (TRUE);
}
