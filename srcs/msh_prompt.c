/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 19:23:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/03 23:15:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static char	*get_pwd(char **env)
{
	char	*ret;
	char	*pwd;
	char	*home;
	char	*tmp;

	pwd = get_env_var(env, "PWD");
	if (!(ret = get_name_from_path(pwd)))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return(ft_strdup("unknown"));
		ret = ft_strdup(get_name_from_path(tmp));
		ft_strdel(&tmp);
	}
	else
	{
		home = get_env_var(env, "HOME");
		if (pwd && home && ft_strcmp(pwd, home) == 0)
			return (ft_strdup("~"));
		return (ft_strdup(ret));
	}
	return (ret);
}

char		*get_prompt(char **env)
{
	char	*ret;
	char	*envprompt;
	char	*pwd;

	if (!(envprompt = get_env_var(env, "MSH_PROMPT")))
	{
		pwd = get_pwd(env);
		ret = ft_strnew(33 + ft_strlen(pwd));
		ft_strcpy(ret, "\033[1;36mminishell:");
		ft_strcat(ret, "\033[1;33m");
		ft_strcat(ret, pwd);
		ft_strcat(ret, "\033[0;39m$ ");
		ft_strdel(&pwd);
	}
	else
		ret = ft_strdup(envprompt);
	return (ret);
}
