/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:22:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/13 23:51:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static void	fill_bltn(t_cmd *cmd, char *line_cmd)
{
	char			*nptr;
	unsigned int	idx;
	static int		(*bltns_funcs[])(int, char **, char ***) = {&echo_bltn,
		&cd_bltn, &exit_bltn, &env_bltn, &setenv_bltn, &unsetenv_bltn,
		NULL};

	idx = 0;
	nptr = SH_BLTNS;
	while (idx < sizeof(bltns_funcs) / sizeof(*bltns_funcs) && *nptr)
	{
		if (ft_strcmp(line_cmd, nptr) == 0)
		{
			cmd->builtin = bltns_funcs[idx];
			return ;
		}
		nptr += ft_strlen(nptr) + 1;
		idx++;
	}
}

char		*get_cmd_path(char *line_cmd, char **env)
{
	char			*env_path;
	char			**paths;
	char			**tmp;
	char			*ret;

	if (!line_cmd)
		return (NULL);
	if (ft_strchr(line_cmd, '/') || !(env_path = get_env_var(env, "PATH")))
		return (line_cmd);
	paths = ft_strsplit(env_path, ':');
	tmp = paths;
	ret = NULL;
	while (*tmp)
	{
		if ((ret = search_dir_for_file(*tmp, line_cmd)))
			break ;
		tmp++;
	}
	ft_tabfree(&paths);
	return ((!ret) ? line_cmd : ret);
}

t_cmd		*interpret_cmd(char *cline, char **env)
{
	t_cmd	*ret;
	t_cmd	*new;
	char	**psplit;
	char	**bw;

	ret = NULL;
	psplit = ft_strsplit(cline, '|');
	bw = psplit;
	while (*bw)
	{
		new = ft_cmdnew();
		new->c_argv = ft_strsplit(*bw, ' ');
		fill_bltn(new, *new->c_argv);
		new->c_path = (!new->builtin) ? get_cmd_path(*new->c_argv, env) : NULL;
		pipe(new->c_pfd);
		ft_cmdpush(&ret, new);
		bw++;
	}
	ft_tabfree(&psplit);
	return (ret);
}
