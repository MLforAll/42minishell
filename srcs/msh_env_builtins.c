/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/26 22:40:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		env_bltn(int ac, char **av, char ***env)
{
	if (ac > 3)
		return (1);
	ft_puttab(*env, NULL);
	if (ac > 1)
		ft_putendl(av[1]);
	return (0);
}

int		setenv_bltn(int ac, char **av, char ***env)
{
	char	*eq;
	char	*var;
	char	*value;

	if (ac > 3)
	{
		ft_putendl_fd("msh: setenv: Too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ac == 1)
		return (env_bltn(1, NULL, env));
	if (!(eq = ft_strchr(av[1], '=')))
		return (1);
	var = ft_strnew(eq - av[1]);
	ft_strncpy(var, av[1], eq - av[1]);
	value = av[1] + (eq - av[1]) + 1;
	add_env_var(env, (const char*)var, value);
	ft_strdel(&var);
	return (0);
}

int		unsetenv_bltn(int ac, char **av, char ***env)
{
	if (ac == 1)
		return (1);
	del_env_var(env, av[1]);
	return (0);
}
