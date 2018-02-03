/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/03 22:19:45 by kdumarai         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

int		setenv_bltn(int ac, char **av, char ***env)
{
	if (ac > 3)
	{
		ft_putendl_fd("msh: setenv: Too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ac == 1)
		return (env_bltn(1, NULL, env));
	set_env_from_str(env, av[1]);
	return (EXIT_SUCCESS);
}

int		unsetenv_bltn(int ac, char **av, char ***env)
{
	if (ac == 1)
		return (EXIT_FAILURE);
	del_env_var(env, av[1]);
	return (EXIT_SUCCESS);
}

int		exit_bltn(int ac, char **av, char ***env)
{
	(void)env;
	if (ac > 2)
		return (msh_err(MSH_ERR_TMARG, av[0], NULL));
	exit((ac > 1) ? ft_atoi(av[1]) : EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
