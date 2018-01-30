/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 23:01:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int		setenv_bltn(int ac, char **av, char ***env)
{
	if (ac > 3)
	{
		ft_putendl_fd("msh: setenv: Too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ac == 1)
		return (env_bltn(1, NULL, env));
	set_env_from_str(env, av[1]);
	return (0);
}

int		unsetenv_bltn(int ac, char **av, char ***env)
{
	if (ac == 1)
		return (1);
	del_env_var(env, av[1]);
	return (0);
}
