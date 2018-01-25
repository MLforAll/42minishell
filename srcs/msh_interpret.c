/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:22:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 21:48:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static void	fill_bltn(t_cmd *cmd, char *line_cmd)
{
	if (!ft_strcmp(line_cmd, "echo"))
		cmd->builtin = &echo_bltn;
	else if (!ft_strcmp(line_cmd, "exit"))
		cmd->builtin = &exit_bltn;
}

static char	*get_cmd_path(char *line_cmd, char **env)
{
	char	*env_path;
	char	**paths;
	char	**tmp;
	char	*ret;

	if (ft_strchr(line_cmd, '/') || !(env_path = get_env_var("PATH", env)))
		return (line_cmd);
	paths = ft_strsplit(env_path, ':');
	tmp = paths;
	while (*tmp)
	{
		if ((ret = search_dir_for_exec(*tmp, line_cmd)))
			break ;
		tmp++;
	}
	ft_tabfree(&paths);
	return ((!ret) ? line_cmd : ret);
}

t_cmd		*get_cmd_list(char *line, char **env)
{
	char		**cmds;
	char		**bw;
	t_cmd		*ret;
	t_cmd		*new;

	ret = NULL;
	cmds = ft_strsplit(line, ';');
	bw = cmds;
	while (*bw)
	{
		new = ft_cmdnew();
		new->c_argv = ft_strsplit(*bw, ' ');
		fill_bltn(new, *new->c_argv);
		new->c_path = get_cmd_path(*new->c_argv, env);
		if (ft_strchr(new->c_path, '/') && access(new->c_path, X_OK))
		{
			msh_err(2, new->c_path);
			ft_cmddelone(&new);
		}
		ft_cmdpb(&ret, new);
		bw++;
	}
	ft_tabfree(&cmds);
	return (ret);
}
