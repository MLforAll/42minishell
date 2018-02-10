/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 23:00:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/10 20:08:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static int	get_env_opt_code(char c)
{
	if (c == 'i')
		return (0x1);
	if (c == 'v')
		return (0x2);
	return (0);
}

static int	get_env_opts(int ac, char **av, int *idx)
{
	int				ret;
	unsigned int	sidx;

	ret = 0;
	if (ac == 1)
		return (0);
	while (av[*idx])
	{
		if (av[*idx][0] == '-')
		{
			sidx = 1;
			while (av[*idx][sidx])
				ret |= get_env_opt_code(av[*idx][sidx++]);
			(*idx)++;
		}
		else
			break ;
	}
	return (ret);
}

int			env_bltn(int ac, char **av, char ***env)
{
	char			**new_env;
	int				idx;
	int				opts;
	t_cmd			*cmd;

	idx = 1;
	opts = get_env_opts(ac, av, &idx);
	new_env = *env;
	if (opts & 0x1)
		new_env = ft_tabnew();
	else if (ac > 1)
		new_env = ft_tabdup((const char**)*env);
	while (ac > 1 && av[idx])
	{
		if (!ft_strchr(av[idx], '='))
			break ;
		set_env_from_str(&new_env, av[idx]);
		idx++;
	}
	if (!av[idx])
		ft_puttab(new_env, NULL);
	else
	{
		cmd = ft_cmdnew();
		cmd->c_path = get_cmd_path(av[idx], *env);
		cmd->c_argv = ft_tabdup((const char**)(av + idx));
		exec_cmd(cmd, &new_env);
	}
	if (new_env != *env)
		ft_tabfree(&new_env);
	return (EXIT_SUCCESS);
}
