/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/31 21:21:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int			echo_bltn(int ac, char **av, char ***env)
{
	int		nonl;

	(void)env;
	nonl = 0;
	if (ac > 1 && ft_strcmp(av[1], "-n") == 0)
	{
		nonl = 1;
		av++;
	}
	while (*(++av))
	{
		ft_putstr(*av);
		if (*(av + 1))
			ft_putchar(' ');
	}
	if (!nonl)
		ft_putchar('\n');
	return (0);
}

static void	chg_cd_env(char ***env, char *bkp, int old)
{
	char	*pathname;
	char	*tmp;

	tmp = NULL;
	if (old)
		tmp = get_env_var(*env, "PWD");
	if (old)
		pathname = (tmp) ? tmp : bkp;
	else
		pathname = (tmp) ? tmp : getcwd(NULL, 0);
	set_env_var(env, old ? "OLDPWD" : "PWD", pathname);
	if (pathname != tmp)
		ft_strdel(&pathname);
}

int			cd_bltn(int ac, char **av, char ***env)
{
	char	*path_cd;
	char	*pathname;
	char	*oldpwd;

	path_cd = (ac == 1) ? get_env_var(*env, "HOME") : av[1];
	oldpwd = NULL;
	if (ac > 1 && ft_strcmp(av[1], "-") == 0)
	{
		if (!(oldpwd = get_env_var(*env, "OLDPWD")))
			return (msh_err(MSH_ERR_NOSET, av[0], "OLDPWD"));
		else
			path_cd = oldpwd;
	}
	if (!path_cd || access(path_cd, F_OK) == -1)
		return (msh_err(MSH_ERR_NOENT, av[0], path_cd));
	if (path_cd == oldpwd)
		ft_putendl(path_cd);
	pathname = getcwd(NULL, 0);
	if (chdir(path_cd) == -1)
	{
		ft_strdel(&pathname);
		return (msh_err(MSH_ERR_PERM, av[0], path_cd));
	}
	chg_cd_env(env, pathname, YES);
	chg_cd_env(env, pathname, NO);
	return (0);
}

int			exit_bltn(int ac, char **av, char ***env)
{
	(void)env;
	if (ac > 2)
		return (msh_err(MSH_ERR_TMARG, av[0], NULL));
	exit((ac > 1) ? ft_atoi(av[1]) : 0);
	return (0);
}
