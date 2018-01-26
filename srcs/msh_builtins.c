/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/26 22:42:15 by kdumarai         ###   ########.fr       */
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

	path_cd = (ac == 1) ? get_env_var(*env, "HOME") : av[1];
	if (!path_cd || access(path_cd, X_OK) == -1)
	{
		ft_putstr_fd("msh: cd: ", STDERR_FILENO);
		if (path_cd)
			ft_putstr_fd(path_cd, STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	if (chdir(path_cd) == -1)
	{
		ft_putstr_fd("msh: cd: ", STDERR_FILENO);
		if (path_cd)
			ft_putstr_fd(path_cd, STDERR_FILENO);
		ft_putendl_fd("Can't cd to directory", STDERR_FILENO);
		return (1);
	}
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
