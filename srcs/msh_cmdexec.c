/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 22:20:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

static void	cmd_err(char *path)
{
	int		noent_msg;

	noent_msg = ft_strchr(path, '/') ? MSH_ERR_NOCMD : MSH_ERR_NOENT;
	if (access(path, F_OK) == -1)
		msh_err(noent_msg, NULL, path);
	else if (access(path, X_OK) == -1)
		msh_err(MSH_ERR_PERM, NULL, path);
	else
		msh_err(MSH_ERR_UNDEFINED, NULL, path);
}

int			exec_cmd(t_cmd *cmd, char ***env)
{
	pid_t	pid;
	int		exval;

	exval = 0;
	if (cmd->builtin)
	{
		return ((cmd->builtin)((int)ft_tablen((const char**)cmd->c_argv), \
			cmd->c_argv, env));
	}
	pid = fork();
	if (pid == 0)
	{
		set_env_var(env, "_", cmd->c_path);
		execve(cmd->c_path, cmd->c_argv, *env);
		cmd_err(cmd->c_path);
		exit(127);
	}
	wait4(pid, &exval, 0, NULL);
	return (WEXITSTATUS(exval));
}

int			exec_cmds(t_cmd *allcmds, char ***env)
{
	int		ret;

	while (allcmds)
	{
		ret = exec_cmd(allcmds, env);
		allcmds = allcmds->next;
	}
	return (ret);
}
