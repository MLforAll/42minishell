/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:28:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int		echo_bltn(int ac, char **av, char ***env)
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

int		cd_bltn(int ac, char **av, char ***env)
{
	char	*path_cd;
	char	*pathname;
	char	*oldpwd;

	path_cd = (ac == 1) ? get_env_var(*env, "HOME") : av[1];
	oldpwd = NULL;
	if (ac > 1 && ft_strcmp(av[1], "-") == 0)
		path_cd = (oldpwd = get_env_var(*env, "OLDPWD"));
	if (!path_cd || access(path_cd, X_OK) == -1)
	{
		msh_err(2, av[0], path_cd);
		return (1);
	}
	if (path_cd == oldpwd)
		ft_putendl(path_cd);
	if (chdir(path_cd) == -1)
	{
		msh_err(3, av[0], path_cd);
		return (1);
	}
	chg_env_var(*env, "OLDPWD", get_env_var(*env, "PWD"));
	pathname = getcwd(NULL, 0);
	chg_env_var(*env, "PWD", pathname);
	free(pathname);
	return (0);
}

int		exit_bltn(int ac, char **av, char ***env)
{
	(void)ac;
	(void)av;
	(void)env;
	exit(0); // Not definitive
	return (0);
}
