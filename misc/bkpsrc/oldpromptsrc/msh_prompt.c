/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 19:23:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 23:09:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include <pwd.h>
#include <stdlib.h>
#include "minishell.h"

static void	get_hostname_username(t_prompt *dest)
{
	char			hostname[MAXHOSTNAMELEN + 1];
	char			*dot;
	uid_t			puid;
	struct passwd	*ppw;

	if (gethostname(hostname, MAXHOSTNAMELEN) == -1)
		dest->hostname = NULL;
	else
	{
		if ((dot = ft_strchr(hostname, '.')))
			dest->hostname = ft_strsub(hostname, 0, dot - hostname);
		else
			dest->hostname = ft_strdup(hostname);
	}
	puid = getuid();
	if (!(ppw = getpwuid(puid)))
		dest->username = NULL;
	else
		dest->username = ft_strdup(ppw->pw_name);
}

static char	*get_pwd(char **env)
{
	char			*ret;
	char			*pwd;
	char			*home;
	char			*tmp;

	pwd = get_env_var(env, "PWD");
	if (!(ret = get_name_from_path_2(pwd)))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return (ft_strdup("unknown"));
		ret = ft_strdup(get_name_from_path(tmp));
		ft_strdel(&tmp);
	}
	else
	{
		home = get_env_var(env, "HOME");
		if (pwd && home && ft_strcmp(pwd, home) == 0)
		{
			free(ret);
			return (ft_strdup("~"));
		}
	}
	return (ret);
}

static char	*get_prompt_str(t_prompt *dprompt)
{
	char	*ret;

	if (!dprompt->pwd || !dprompt->hostname || !dprompt->username)
		return (ft_strdup(SH_PLAIN_PROMPT));
	ret = ft_strnew(25 + ft_strlen(dprompt->pwd) + \
		ft_strlen(dprompt->hostname) + ft_strlen(dprompt->username));
	ft_strcpy(ret, "\033[1;36m");
	ft_strcat(ret, dprompt->hostname);
	ft_strcat(ret, ":\033[1;33m");
	ft_strcat(ret, dprompt->pwd);
	ft_strcat(ret, "\033[0;39m ");
	ft_strcat(ret, dprompt->username);
	ft_strcat(ret, "$ ");
	return (ret);
}

char		*get_prompt(char **env)
{
	char			*ret;
	char			*envprompt;
	t_prompt		dprompt;

	if (!(envprompt = get_env_var(env, "MSH_PROMPT")))
	{
		dprompt.pwd = get_pwd(env);
		get_hostname_username(&dprompt);
		ret = get_prompt_str(&dprompt);
		ft_strdel(&dprompt.hostname);
		ft_strdel(&dprompt.pwd);
		ft_strdel(&dprompt.username);
		return (ret);
	}
	return (ft_strdup(envprompt));
}
