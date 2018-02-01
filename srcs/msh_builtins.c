/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/01 22:27:24 by kdumarai         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

static void	chg_cd_env(char ***env, char *bkp, int old)
{
	char	*pathname;
	char	*tmp;

	tmp = NULL;
	if (old && !bkp)
		return ;
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

static char	*get_cd_path(int ac, char **av, char **env)
{
	char	*ret;
	char	*oldpwd;

	oldpwd = NULL;
	if (ac == 1)
	{
		if (!(ret = get_env_var(env, "HOME")))
			msh_err(MSH_ERR_NOSET, av[0], "HOME");
	}
	else
		ret = av[1];
	if (ac > 1 && ft_strcmp(av[1], "-") == 0)
	{
		if (!(oldpwd = get_env_var(env, "OLDPWD")))
			msh_err(MSH_ERR_NOSET, av[0], "OLDPWD");
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
		return (msh_err(access(path_cd, F_OK) == -1 ? MSH_ERR_NOENT \
									: MSH_ERR_PERM, av[0], path_cd));
	}
	chg_cd_env(env, bkp, YES);
	chg_cd_env(env, NULL, NO);
	return (EXIT_SUCCESS);
}

int			exit_bltn(int ac, char **av, char ***env)
{
	(void)env;
	if (ac > 2)
		return (msh_err(MSH_ERR_TMARG, av[0], NULL));
	exit((ac > 1) ? ft_atoi(av[1]) : EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
