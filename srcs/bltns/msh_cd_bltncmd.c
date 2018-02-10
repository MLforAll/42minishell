/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_bltncmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/11 00:03:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static void	chg_cd_env(char ***env, char *bkp, int old)
{
	char	*pathname;
	char	*tmp;

	if ((old && !bkp) || (!old && bkp && ft_strcmp(bkp, ".") == 0))
		return ;
	tmp = get_env_var(*env, "PWD");
	if (old)
		pathname = (tmp) ? tmp : bkp;
	else if (bkp && tmp && *bkp != '/')
	{
		if (ft_strcmp(bkp, "..") == 0)
			pathname = get_basedir(tmp);
		else
		{
			pathname = ft_strnew(ft_strlen(tmp) + ft_strlen(bkp) + 1);
			ft_strcpy(pathname, tmp);
			ft_strcat(pathname, "/");
			ft_strcat(pathname, bkp);
		}
	}
	else
		pathname = getcwd(NULL, 0);
	set_env_var(env, old ? "OLDPWD" : "PWD", pathname);
	if (pathname != tmp && pathname)
		free(pathname);
}

static char	*get_cd_path(int ac, char **av, char **env)
{
	char	*ret;
	char	*oldpwd;

	oldpwd = NULL;
	if (ac == 1)
	{
		if (!(ret = get_env_var(env, "HOME")))
			msh_err(SH_ERR_NOSET, av[0], "HOME");
	}
	else
		ret = av[1];
	if (ac > 1 && ft_strcmp(av[1], "-") == 0)
	{
		if (!(oldpwd = get_env_var(env, "OLDPWD")))
			msh_err(SH_ERR_NOSET, av[0], "OLDPWD");
		ret = oldpwd;
	}
	if (ret && ret == oldpwd)
		ft_putendl(ret);
	return (ret);
}

int			cd_bltn(int ac, char **av, char ***env)
{
	char	*path_cd;
	char	*bkp;

	if (!(path_cd = get_cd_path(ac, av, *env)))
		return (EXIT_FAILURE);
	bkp = getcwd(NULL, 0);
	if (chdir(path_cd) == -1)
	{
		ft_strdel(&bkp);
		return (msh_err(access(path_cd, F_OK) == -1 ? SH_ERR_NOENT \
									: SH_ERR_PERM, av[0], path_cd));
	}
	chg_cd_env(env, bkp, YES);
	free(bkp);
	chg_cd_env(env, path_cd, NO);
	return (EXIT_SUCCESS);
}
